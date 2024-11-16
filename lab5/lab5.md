# Spectre Attack Lab

First, let's go over some **concepts**:

1. **Speculative Execution:** CPU predicts the outcome of an operation and begins executing instructions ahead of time to improve performance. If the prediction is wrong, the CPU *discards the results.* (It can lead to security risks, like `Spectre` and `Meltdown`).

2. **Out-of-order Execution:** CPU executes instructions in a different order to optimize resource usage, without predicting outcomes.

3. **Side Channels:** Indirect ways through which sensitive information can be leaked, such as through *timing*, power use, or electromagnetic emissions, allowing attackers to gain access to data *without directly interacting with the system.*

- Watch this [Youtube video](https://youtu.be/syAdX44pokE?si=l5CXhKV4GIKLq6iF) for a good visual explaination.

## What are Spectre & Meltdown Attacks?
| **Aspect**| **Spectre**| **Meltdown**|
|-----|-----|-----|
| **Vulnerability**     | Exploits speculative execution in CPUs.    | Exploits memory isolation in CPUs.      |
| **Target**            | Can affect multiple processes.            | Primarily affects kernel memory.        |
| **Attack Method**     | Tricks CPU into executing unintended instructions. | Allows reading privileged kernel memory. |
| **Impact**            | Leaks sensitive data across processes.    | Allows attackers to read kernel data.   |
| **Mitigation**        | Requires both software and hardware fixes. | Requires software patches for isolation.|
| **Scope**             | More complex, can target a wider range of systems. | Easier to exploit, more directly impacts system memory. |

Check out these videos that explain the attacks very well: 
1. [Meltdown & Spectre vulnerabilities - Simply Explained](https://youtu.be/bs0xswK0eZk?si=TqQPM8AXiF7c8ty_)
2. [Spectre & Meltdown - Computerphile](https://youtu.be/I5mRwzVvFGE?si=fWR-EvfntkoAs7MK)
3. [Spectre attack explained like you're five](https://youtu.be/q3-xCvzBjGs?si=JGkivo4Ve6gdYRwL)
4. [Meltdown explained like you're five](https://youtu.be/JSqDqNysycQ?si=xuaS4rGSKK-GHHXH)

## Task 1: Reading from Cache versus from Memory:

Both the Meltdown and Spectre attacks **use CPU cache as a side channel** to steal a protected secret.

![CPU Cache hit & miss](https://github.com/moooninjune/SEED-labs/blob/cca8d6b2b747d2d3b4be1f9681d3da227fc873b9/images/lab5-CPU-Cache.jpg)

1. Compile and run the `CacheTime.c` file.

2. Which elements from the array are in the cache?

    The accesses of array[3\*4096] and array[7\*4096] are extremely *faster* than that of the other elements because they're being brought from the cache.

3. Run the program at least 10 times and describe your observations.

    The access times of each element seems to be randomly various among 10 attempts.


## Task 2: Side Channel Attacks via CPU Caches:
The objective of this task is to use the **side channel** to extract a secret value used by the victim function that uses a secret value as index to load some values from an array.

The technique that we will be using is called `FLUSH+RELOAD`.

![Side-Channel-Attack](https://github.com/moooninjune/SEED-labs/blob/f4bce5cd3b29ddd107bbcd313205e83f8793b04a/images/lab5-sidechannel-attack.jpg)

1. **Flush** the array from the cache to ensure it's not cached (Empty the cache).

2. Call the victim function, which accesses an array element based on the secret, causing it to be cached.

3. **Reload** the array and measure the **time** for each element. A fast reload time indicates the element is cached, revealing the accessed element and the secret value.

Compile and run the `FlushReload.c` file.
```bash
# output
array[94*4096 + 1024] is in cache.
The Secret = 94.
```

- Run the program for at least 20 times, and count how many times you will get the secret correctly. 

- You can also adjust the threshold `CACHE_HIT_THRESHOLD` to the one derived from Task 1 (80 is used in this code).

## Task 3: Out-of-Order Execution and Branch Prediction:

CPU makers made a severe mistake in the design of the out-of-order execution. They wipe out the effects of the out-of-order execution on registers and memory if such an execution is not supposed to happen, so the execution does not lead to any visible effect. However, **they forgot one thing, the effect on CPU caches.**

During the out-of-order execution, the referenced memory is fetched into a register and is **also stored in the cache.** If the results of the out-of-order execution have to be discarded, the caching caused by the execution should also be discarded.

```cpp
//example
data = 0;
if (x < size) {
data = data + 5;
```
![Speculative execution (out-of-order execution)](https://github.com/moooninjune/SEED-labs/blob/fae6a264028f8e57d019e8a3664261470cfaee16/images/lab5-speculative-execution.jpg)

1. If we'd like a particular branch to be taken in a speculative execution, we should train the CPU, so our selected branch can become the prediction result. In the code `SpectreExperiment.c`, we trained the CPU through the `for` loop.

2. We invoked `victim()` with a small argument (from 0 to 9). These values are less than the value `size`, so the true-branch of the `if-condition` is always taken.

```c
// Train the CPU to take the true branch inside victim()
for (i = 0; i < 10; i++)
victim(i);
```
```c
void victim(size_t x) 
{
if (x < size) //this is the branch (if-condition)
temp = array[x * 4096 + DELTA];
}
```

3. Once the CPU is trained, we pass a larger value (97) to the `victim()` function. This value is larger than `size`, so the false-branch of the if-condition inside `victim()` will be taken in the *actual* execution. However, we have flushed the variable `size` from the memory, so getting its value from the memory may take a while. **This is when the CPU will make a prediction, and start speculative execution.**
```c
// Exploit the out-of-order execution
_mm_clflush(&size);
for (i = 0; i < 256; i++)
    _mm_clflush(&array[i*4096 + DELTA]);
victim(97);
```

- Compile and run the `SpectreExperiment.c` file.
```bash
# output
array[97*4096 + 1024] is in cache.
The Secret = 97.
```
Because 97 >= size, the `if-condition` inside the `victim()` function should not be executed. But, it works!

4. Comment out the following line and execute again.
```c
_mm_clflush(&size);
```
It'll output nothing. The function `_mm_clflush()` flushes all content in caches that contains variable `size`, which ensure the cache is not influenced by `size` during each call of `victim`.

5. Replace `victim(i);` inside the `for` loop with `victim(i + 20);`, and run the code again.
```c
// Train the CPU to take the true branch inside victim()
for (i = 0; i < 10; i++)
//victim(i);
victim(i + 20);
```
It also fails to give any output. Because when `i > size`, the statement will be not executed.


## Task 4: The Spectre Attack:

Most CPUs that use the out-of-order execution do not clean the cache, so some traces of it is left behind. The Spectre attack uses these traces to steal protected secrets.

Secrets can be in the same or different processes:

| **Aspect** | **Secrets within the Same Process** | **Secrets in Other Processes**|
|----------|----------|----------|
| **Protection Mechanism** | Software mechanisms like sandboxes.                                                                       | Hardware-level process isolation.                                                                 |
| **Spectre Exploit**      | Exploits *out-of-order* execution to bypass protections and access protected code branches.                 | Technically possible but much harder due to strong hardware isolation.                            |
| **Ease of Attack**       | Easier to steal data, e.g., between web pages in the same browser process.                                | Much harder because processes are isolated from each other.                                       |

- **There are two types of regions:** Restricted
region and Non-Restricted region. The restriction is usually achieved via an `if-condition`.

![The buffer and the protected secret](https://github.com/moooninjune/SEED-labs/blob/dfd1036fed00336a97f9db67d21a839fa3df1ca1/images/lab4-task4.jpg)

```c
if (x <= bound_upper && x >= bound_lower)
return buffer[x];

else
return 0;
```

- Compile and run the `SpectreAttack.c` file.
```bash
# output
secret: 0x55b0913f5008 
buffer: 0x55b0913f7018 
index of secret (out of bound): -8208 
array[0*4096 + 1024] is in cache.
The Secret = 0().
# here :
array[83*4096 + 1024] is in cache.
The Secret = 83(S).
```

## Task 5: Improve the Attack Accuracy:

- Compile and run the `SpectreAttackImproved.c` file.
```bash
# output
Reading secret value at index -8208
The secret value is 83(S)
The number of hits is 106
```

## Task 6: Steal the Entire Secret String:
In the previous task, we just read the first character of the secret string. In this task, we need to print out **the entire string** using the Spectre attack.

- Please write your own code or extend the code in Task 5:
```c

```