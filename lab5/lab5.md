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

## Tasks 1 and 2: Side Channel Attacks via CPU Caches: 
Both the Meltdown and Spectre attacks **use CPU cache as a side channel** to steal a protected secret.

![CPU Cache hit & miss](https://github.com/moooninjune/SEED-labs/blob/cca8d6b2b747d2d3b4be1f9681d3da227fc873b9/images/lab5-CPU-Cache.jpg)

### Task 1: Reading from Cache versus from Memory:
1. Compile and run the `CacheTime.c` file.

2. Which elements from the array are in the cache?

    The accesses of array[3/*4096] and array[7/*4096] are extremely *faster* than that of the other elements because they're being brought from the cache.

3. Run the program at least 10 times and describe your observations.

    The access times of each element seems to be randomly various among 10 attempts.


### Task 2: Using Cache as a Side Channel:
The objective of this task is to use the **side channel** to extract a secret value used by the victim function that uses a secret value as index to load some values from an array.

The technique that we will be using is called `FLUSH+RELOAD`.

![Side-Channel-Attack](https://github.com/moooninjune/SEED-labs/blob/f4bce5cd3b29ddd107bbcd313205e83f8793b04a/images/lab5-sidechannel-attack.jpg)

1. **Flush** the array from the cache to ensure it's not cached.

2. Call the victim function, which accesses an array element based on the secret, causing it to be cached.

3. **Reload** the array and measure the **time** for each element. A fast reload time indicates the element is cached, revealing the accessed element and the secret value.


