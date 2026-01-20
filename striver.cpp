/*-------------
   Chhono
-------------*/
#include <bits/stdc++.h>
#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>
typedef signed long long ll;
typedef unsigned long long ull;
typedef long double ld;
using namespace std;

//   taskkill -im striver.exe -f
// cout<<fixed<<setprecision(12)<<res<<endl;
// printf("%.10f\n",diff );

#define fastio()                                                               \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
// #define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define PI 3.141592653589793238462
#define set_bits(x) __builtin_popcountll(x)
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/*---------------------------------------------------------------------------------------------------------------------------*/
ll gcd(ll a, ll b) {
  if (b > a) {
    return gcd(b, a);
  }
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}
ll expo(ll a, ll b, ll mod) {
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * a) % mod;
    a = (a * a) % mod;
    b = b >> 1;
  }
  return res;
}
void extendgcd(ll a, ll b, ll *v) {
  if (b == 0) {
    v[0] = 1;
    v[1] = 0;
    v[2] = a;
    return;
  }
  extendgcd(b, a % b, v);
  ll x = v[1];
  v[1] = v[0] - v[1] * (a / b);
  v[0] = x;
  return;
} // pass an arry of size1 3
ll mminv(ll a, ll b) {
  ll arr[3];
  extendgcd(a, b, arr);
  return arr[0];
} // for non prime b
ll mminvprime(ll a, ll b) { return expo(a, b - 2, b); }
bool revsort(ll a, ll b) { return a > b; }
ll combination(ll n, ll r, ll m, ll *fact, ll *ifact) {
  ll val1 = fact[n];
  ll val2 = ifact[n - r];
  ll val3 = ifact[r];
  return (((val1 * val2) % m) * val3) % m;
}
void google(int t) { cout << "Case #" << t << ": "; }
vector<ll> sieve(int n) {
  int *arr = new int[n + 1]();
  vector<ll> vect;
  for (int i = 2; i <= n; i++)
    if (arr[i] == 0) {
      vect.push_back(i);
      for (int j = 2 * i; j <= n; j += i)
        arr[j] = 1;
    }
  return vect;
}
ll mod_add(ll a, ll b, ll m) {
  a = a % m;
  b = b % m;
  return (((a + b) % m) + m) % m;
}
ll mod_mul(ll a, ll b, ll m) {
  a = a % m;
  b = b % m;
  return (((a * b) % m) + m) % m;
}
ll mod_sub(ll a, ll b, ll m) {
  a = a % m;
  b = b % m;
  return (((a - b) % m) + m) % m;
}
// ll mod_div(ll a, ll bbbbb, ll m) {a = a % m; b = b % m; return (mod_mul(a,
// mminvprime(b, m), m) + m) % m;}  //only for prime m
ll phin(ll n) {
  ll number = n;
  if (n % 2 == 0) {
    number /= 2;
    while (n % 2 == 0)
      n /= 2;
  }
  for (ll i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) {
      while (n % i == 0)
        n /= i;
      number = (number / i * (i - 1));
    }
  }
  if (n > 1)
    number = (number / n * (n - 1));
  return number;
} // O(sqrt(N))
ll getRandomNumber(ll l, ll r) {
  return uniform_int_distribution<ll>(l, r)(rng);
}
void getRandomArray(ll len, ll start, ll end) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<ll> dis(start, end);
  for (ll i = 0; i < len; i++) {
    std::cout << dis(gen) << ",";
  }
  std::cout << std::endl;
}

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
/*--------------------------------------------------------------------------------------------------------------------------*/

#include <chrono>
#include <memory>
#include <thread>

struct Timer {
  chrono::time_point<std::chrono::high_resolution_clock> start, end;
  chrono::duration<float> duration;

  Timer() { start = chrono::high_resolution_clock::now(); }

  ~Timer() {
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Timer took " << duration.count() << endl;
  }
};

void Function() {
  Timer t;
  for (int i = 0; i < 100; i++) {
    cout << "hi chhono" << endl;
  }
}

atomic<bool> s_Finished(false);

void doWork() {
  int i = 0;
  cout << "Thread id" << this_thread::get_id() << endl;
  while (!s_Finished) {
    cout << i << ". Working...\n";
    i++;
    this_thread::sleep_for(1s);
  }
}

mutex coutMutex;
void safePrint(int i) {
  coutMutex.lock();
  cout << i << ". Working\n";
  coutMutex.unlock();
}

int main1() {
  // Input
  //  #ifndef ONLINE_JUDGE
  //  freopen("input.txt","r",stdin);
  //  freopen("output.txt","w",stdout);
  // #endif

  // auto start=chrono::high_resolution_clock::now();
  // this_thread::sleep_for(1s);
  // auto end=chrono::high_resolution_clock::now();

  // chrono::duration<float> duration=end-start;
  // cout<<duration.count()<<endl;

  // Function();

  // thread worker(doWork);
  // std::cin.get();
  // s_Finished=true;
  // worker.join();
  // cout<<"Finished..."<<endl;
  // cout<<"Main-thread id="<<this_thread::get_id()<<endl;
  // std::cin.get();

  //   safePrint(10);
  return 0;
}

// using normal int------------------------------------------------------
queue<int> buffer;
condition_variable cv;
mutex mtx;

void producer() {
  for (int i = 0; i < 7; i++) {
    this_thread::sleep_for(chrono::milliseconds(500));
    lock_guard<mutex> lock(mtx);
    {
      buffer.push(i);
      cout << "Produced " << i << endl;
    }
    cv.notify_one();
  }
}

void consumer() {
  while (true) {
    unique_lock<mutex> lock(mtx);

    // magic
    cv.wait(lock, [] { return !buffer.empty(); });
    int data = buffer.front();
    buffer.pop();
    cout << "Consumed " << data << endl;
    if (data == 6)
      return;
  }
}

// int main() {
//   thread t1(consumer);
//   thread t2(producer);
//   t1.join();
//   t2.join();
//   return 0;
// }

// using smart pointers-----------------------------------------

// condition_variable cv;
// mutex mtx;
// queue<unique_ptr<int>> buffer;

// void producer() {
//   for (int i = 0; i < 5; i++) {
//     // this_thread::sleep_for(chrono::milliseconds(500));
//     unique_ptr<int> dataPtr = make_unique<int>(i);
//     {
//       lock_guard<mutex> lock(mtx);
//       buffer.push(std::move(dataPtr));
//       cout << "Produced " << i << " ownership given to queue" << endl;
//     }
//     cv.notify_all();
//   }
// }

// void consumer() {
//   while (true) {
//     unique_lock<mutex> lock(mtx);
//     cv.wait(lock, [] { return !buffer.empty(); });
//     auto consumedData = std::move(buffer.front());
//     buffer.pop();
//     cout << "Consumed " << (*consumedData) << " ownership given to consumer"
//          << endl;
//     if (*consumedData == 4)
//       break;
//   }
// }

// int main() {
//   thread t1(producer);
//   thread t2(consumer);
//   t1.join();
//   t2.join();
// }

// abstraction=pure virtual function
// inheritance
// polymerphism=static/dynamic binding
// encapsulation=access modifires

// designing my one memcpy

void *my_memcpy(void *dest, const void *src, size_t n) {
  char *d = (char *)dest;
  const char *s = (const char *)src;

  // Save the starting address to return it later
  void *original_dest = dest;

  // Use > 0 to ensure we copy exactly N bytes
  while (n > 0) {
    *d = *s;
    d++;
    s++;
    n--;
  }

  return original_dest;
}

void *optimized_memcpy(void *dest, const void *src, size_t n) {
  // 1. Still need these for the final "leftover" bytes
  uint8_t *d_byte = (uint8_t *)dest;
  const uint8_t *s_byte = (const uint8_t *)src;

  // 2. Cast to 8-byte (64-bit) pointers
  uint64_t *d64 = (uint64_t *)dest;
  const uint64_t *s64 = (const uint64_t *)src;

  // 3. Copy in 8-byte chunks as long as we have at least 8 bytes left
  while (n >= 8) {
    *d64 = *s64; // Moves 8 bytes in ONE clock cycle
    d64++;       // Jumps the pointer forward by 8 bytes
    s64++;       // Jumps the pointer forward by 8 bytes
    n -= 8;      // We've handled 8 bytes
  }

  // 4. Handle the "Trailing Bytes"
  // If n was 11, we moved 8 bytes, and now 3 bytes are left.
  // We must go back to byte-by-byte for these last 3.
  d_byte = (uint8_t *)d64;
  s_byte = (uint8_t *)s64;

  while (n > 0) {
    *d_byte = *s_byte;
    d_byte++;
    s_byte++;
    n--;
  }
  return dest;
}

void *my_memmove(void *dest, const void *src, size_t n) {
  if (!dest || !src)
    return dest;

  char *d = (char *)dest;
  const char *s = (const char *)src;

  // Case 1: Overlap where dest is ahead of src
  // We must copy BACKWARDS
  if (d > s && d < s + n) {
    // Move pointers to the end of the buffers
    d += n - 1;
    s += n - 1;
    while (n--) {
      *d = *s;
      d--;
      s--;
    }
  }
  // Case 2: No overlap OR dest is behind src
  // Safe to copy FORWARDS
  else {
    while (n--) {
      *d = *s;
      d++;
      s++;
    }
  }

  return dest;
}




//Implement your own sizeof operator------------
template <typename T>
size_t my_sizeof() {
    T arr[2]; // Create an array of two elements
    
    // Get the address of the first and second elements
    // We cast them to char* so the subtraction gives us the result in BYTES
    size_t addr1 = (size_t)&arr[0];
    size_t addr2 = (size_t)&arr[1];
    
    return addr2 - addr1;
}

int main() {
    std::cout << "Size of int: " << my_sizeof<int>() << std::endl;
    std::cout << "Size of double: " << my_sizeof<double>() << std::endl;
    return 0;
}