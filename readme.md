# Reusing the hash computation for multiple lookups

An example of using a single hash computation for looking up in multiple
unordered containers using memoisation.

### build & run
```
> mkdir build
> cd build
> cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ../.
> ninja
> ./one_hash_two_lookup
```
