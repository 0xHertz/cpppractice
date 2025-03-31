#include <iostream>
#include <unordered_set>

/*
这段代码展示了如何为自定义类型（如 `Customer` 类）定义哈希函数，
以便可以将该类型的对象存储在哈希容器（如 `std::unordered_set`）中
*/

class Customer {
    public:
        int id;
        std::string name;
        Customer(int id, const std::string& name) : id(id), name(name) {}
};
/*
方式一：通过重载（）运算符形成了一个防函数（函数对象）
*/
class CustomerHash {
    public:
    size_t operator()(const Customer &c) const {
        size_t h1 = std::hash<int>()(c.id);
        size_t h2 = std::hash<std::string>()(c.name);
        return h1 ^ (h2 << 1); // 组合两个哈希值
    }
};
// Usage
// std::unordered_set<Customer, CustomerHash> customerSet;





/*
方式二：通过指定一个普通函数的方式来通知容器使用哪个哈希函数
*/
size_t customer_hash_func(const Customer &t){
    size_t h1 = std::hash<int>()(c.id);
    size_t h2 = std::hash<std::string>()(c.name);
    return h1 ^ (h2 << 1); // 组合两个哈希值
}
// Usage
// std::unordered_set<Customer, size_t(*)(const Customer&)> customerSet(20, customer_hash_func); // 20是hash中桶的数量
// lambda函数
auto lambda_customer_hash_func = [](const Customer &c) -> size_t {
    size_t h1 = std::hash<int>()(c.id);
    size_t h2 = std::hash<std::string>()(c.name);
    return h1 ^ (h2 << 1); // 组合两个哈希值
};
// Usage
// std::unordered_set<Customer, decltype(customer_hash_func)> customerSet(20, customer_hash_func);




/*
方式三：以std::hash偏特化的方式来定义哈希函数，可以为自定义类型定义哈希函数。这种方式要求将特化定义放在 `std` 命名空间中。
*/
namespace std{
    template<>
    struct hash<Customer> : public __hash_base<size_t,Customer> {
        size_t operator()(const Customer& s) const noexcept {
            // return ...;
        }
    };
}
// Usage
// std::unordered_set<Customer> customerSet;







/*
方式四：使用组合哈希函数,可以使用变参模板来定义一个通用的哈希函数组合器，适用于多个成员变量的组合哈希。
*/
// (4) 组合两个哈希值
template<typename T>
inline void hash_combine(size_t& seed, const T& val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// (3) 处理单个参数的哈希值
template<typename T>
inline void hash_val(size_t& seed, const T& val) {
    hash_combine(seed, val);
}

// (2) 递归处理多个参数的哈希值
template<typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

// (1) 生成最终的哈希值
template<typename... Types>
inline size_t hash_val(const Types&... args) {
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

// 偏特化 `std::hash` 模板
namespace std {
    template<>
    struct hash<Customer> {
        size_t operator()(const Customer &c) const {
            return hash_val(c.id, c.name);
        }
    };
}
// Usage
int main() {
    std::unordered_set<Customer> customerSet;

    // 添加元素
    customerSet.insert(Customer(1, "Alice"));
    customerSet.insert(Customer(2, "Bob"));

    // 查找元素
    Customer c(1, "Alice");
    if (customerSet.find(c) != customerSet.end()) {
        std::cout << "Customer found: " << c.name << std::endl;
    } else {
        std::cout << "Customer not found" << std::endl;
    }

    return 0;
}
