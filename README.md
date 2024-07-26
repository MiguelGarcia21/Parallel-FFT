# Parallel-FFT
FFT is a critical algorithm in signal processing and many scientific applications. The goal is to parallelize the Cooley-Tukey FFT algorithm to handle large datasets more efficiently.

The Fourier Transform is a mathematical tool used to transform a signal from the time domain to the frequency domain. It breaks down a signal into its constituent frequencies, allowing us to analyze the frequency components present in the signal.

This transformation is useful in many areas, such as signal processing, image processing, and data analysis. However, computing the Discrete Fourier Transform (DFT) directly for large datasets can be computationally expensive, as it has a time complexity of O(n^2), where n is the size of the input. 

The Fast Fourier Transform (FFT) is an efficient algorithm that computes the DFT with a significantly reduced time complexity of O(n log n). 

An easy way to understand the purpose of the algorithm is the following:
Imagine we have a large group of 16 people, and we need to ask them a question (for example, how many times have they eaten today). Instead of asking each person individually, which would take a lot of time, we can divide the group in smaller groups, let´s say 2 groups of 8 each, and then continue dividing it until we have the smallest group possible, let´s say 2 people per group will be 8 groups.

Then we take the results of each group and combine them in a specific way to get the result of larger groups. 

In the code, the process is not a "question" as used in the analogy, but it is a transformation of the input signal data to a frequency domain by identifying various components present in it.

In parallel programming, the Cooley-Tukey FFT algorithm can be parallelized by distributing the independent computations across multiple threads. This can further improve the performance, especially for very large datasets, by taking advantage of multi-core and parallel computing architectures. 

In the analogy context, by parallelizing we will have the same process but now we have more people working in asking each group the question, so all of the groups are being asked in a parallel way which reduces the total time.

Below you will find the comparison results of the average time taken for many configurations:
This is the representation of the performance using 4096, 8192, 16384 and 32768 with the serial version of the code and the parallel version with 1, 4 and 8 threads.

Please note, the time is represented in Miliseconds:

![image](https://github.com/user-attachments/assets/bd19280e-78c0-47f6-b380-a15c502c6586)


![image](https://github.com/user-attachments/assets/f9cde8ee-1bb5-47e5-b912-23b361808580)






For better readability, this is a separate chart representing the performance using 65536, 131072, 262144:
![image](https://github.com/user-attachments/assets/0e538960-e737-4901-bc4b-d581697c530a)


![image](https://github.com/user-attachments/assets/ff1e6ed8-cadd-428e-a191-1789b6779cf4)

- We can see a Massive improvement in all charts when jumping from 1 to 4 threads but not much improvement when moving from 4 to 8 threads.
- We see that it is more efficient using the serial version than the Parallel version if we select only one thread, and then when selecting 4 we can see an improvement


