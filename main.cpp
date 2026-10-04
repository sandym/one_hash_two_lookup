
#include <print>
#include <string>
#include <absl/container/flat_hash_map.h>

struct string_hash_memo
{
	std::size_t h{};
	std::string_view sv;
};
inline bool operator==(const string_hash_memo &lhs, const std::string_view &rhs) { return lhs.sv == rhs; }

struct string_hash
{
    using hash_type = std::hash<std::string_view>;
    using is_transparent = void;

    std::size_t operator()(const char* str) const        { return absl::Hash<std::string_view>{}(str); }
    std::size_t operator()(std::string_view str) const   { return absl::Hash<std::string_view>{}(str); }
    std::size_t operator()(std::string const& str) const { return absl::Hash<std::string_view>{}(str); }
    std::size_t operator()(string_hash_memo memo) const  { return memo.h; }
};

template <typename T1, typename T2>
void lookup1(const T1 &m1, const T2 &m2, std::string_view key)
{
	auto it1 = m1.find(key); // lookup, will hash
	if (it1 != m1.end())
		std::print("key: {}, value: {}\n", key, it1->second);
	
	auto it2 = m2.find(key); // lookup, will hash
	if (it2 != m2.end())
		std::print("key: {}, value: {}\n", key, it2->second);
}

template <typename T1, typename T2>
void lookup2(const T1 &m1, const T2 &m2, std::string_view key)
{
	// single hash for 2 lookups
	string_hash_memo memo{ absl::Hash<std::string_view>{}(key), key };

	auto it1 = m1.find(memo); // lookup, reuse hash
	if (it1 != m1.end())
		std::print("key: {}, value: {}\n", key, it1->second);
	
	auto it2 = m2.find(memo); // lookup, reuse hash
	if (it2 != m2.end())
		std::print("key: {}, value: {}\n", key, it2->second);
}

int main()
{
	absl::flat_hash_map<std::string, int, string_hash, std::equal_to<>> m1{
		{ "one", 1 },
		{ "two", 2 },
		{ "three", 3 }
	};
	absl::flat_hash_map<std::string, std::string, string_hash, std::equal_to<>> m2{
		{ "one", "uno" },
		{ "two", "dos" },
		{ "three", "tres" }
	};

	lookup1(m1, m2, "one");
	lookup1(m1, m2, "two");
	lookup1(m1, m2, "three");
	lookup1(m1, m2, "four");

	lookup2(m1, m2, "one");
	lookup2(m1, m2, "two");
	lookup2(m1, m2, "three");
	lookup2(m1, m2, "four");
}
