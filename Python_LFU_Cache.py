from collections import defaultdict, OrderedDict

class LFUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.min_freq = 0
        self.key_to_val = {}  # {key: value}
        self.key_to_freq = {}  # {key: frequency}
        # {frequency: OrderedDict of {key: value}}
        self.freq_to_keys = defaultdict(OrderedDict) 

    def get(self, key):
        if key not in self.key_to_val:
            return -1

        # 1. Update frequency
        old_freq = self.key_to_freq[key]
        self.key_to_freq[key] += 1
        new_freq = old_freq + 1

        # 2. Move key to new frequency list
        val = self.key_to_val[key]
        del self.freq_to_keys[old_freq][key]
        
        # If the old frequency list is empty and it was the minimum frequency, update min_freq
        if not self.freq_to_keys[old_freq] and old_freq == self.min_freq:
            self.min_freq += 1
            
        self.freq_to_keys[new_freq][key] = val
        return val

    def put(self, key, value):
        if self.capacity == 0:
            return

        if key in self.key_to_val:
            self.key_to_val[key] = value
            self.get(key) # Use 'get' to update its frequency
            return

        # Handle capacity limit: Evict LFU key
        if len(self.key_to_val) >= self.capacity:
            # Get the oldest key from the min_freq list (OrderedDict ensures LRU tie-breaker)
            lfu_key, _ = self.freq_to_keys[self.min_freq].popitem(last=False)
            del self.key_to_val[lfu_key]
            del self.key_to_freq[lfu_key]

        # Insert new key
        self.key_to_val[key] = value
        self.key_to_freq[key] = 1
        self.freq_to_keys[1][key] = value
        self.min_freq = 1 # New key always starts at frequency 1

# Example Usage:
cache = LFUCache(2)
print("Put(1, 1)")
cache.put(1, 1) # F: {1: [1]}
print("Put(2, 2)")
cache.put(2, 2) # F: {1: [1, 2]}
print(f"Get(1): {cache.get(1)}") # F: {1: [2], 2: [1]}
print("Put(3, 3)") 
# Capacity reached. Min freq is 1. Key '2' is LFU and LRU at freq 1. Evict 2.
cache.put(3, 3) # F: {1: [3], 2: [1]}
print(f"Get(2): {cache.get(2)}") # Output: -1 (Miss)
print(f"Get(3): {cache.get(3)}") # F: {2: [1, 3]}
