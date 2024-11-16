# Spectre Attack Lab

First, let's go over some **concepts**:

1. **Speculative Execution:** When a CPU predicts the outcome of an operation and begins executing instructions ahead of time to improve performance. If the prediction is wrong, the CPU *discards the results.* (It can lead to security risks, like `Spectre` and `Meltdown`).

2. **Side Channels:** Indirect ways through which sensitive information can be leaked, such as through *timing*, power use, or electromagnetic emissions, allowing attackers to gain access to data *without directly interacting with the system.*

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

### Task 1: Reading from Cache versus from Memory:

### Task 2: Using Cache as a Side Channel:

