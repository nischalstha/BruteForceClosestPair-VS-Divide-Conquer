# BruteForceClosestPair-VS-Divide-Conquer
an empirical and analytical analysis between the brute force closest pair and divide and conquer closest pair algorithm.

The brute force closest pair algorithm and divide-and-conquer closest pair algorithm calculates the distance between two closest coordinates in a set(vector) of a finite number of coordinates. <br />

The brute force closest pair algorithm computes all possible distances for each pair of distinct points and finds a pair with the smallest distance. Whereas, the divide and conquer closest pair computes the closest distance by brute force algorithm if the number of coordinates in a set are less than four but if the number of coordinates are greater than four, the set of coordinates are split into two roughly equal halves computing the closest distance recursively and combining the results at the end.<br />

The set of co-ordinates inputed are sorted in nondecreasing order of their x-coordinates and y- coordinates seperately. The purpose of this study is to perform an empirical analysis of this two methods.<br />

For both methods, the input size is taken as the number of co-ordinates in the set because it determines the number of basic operations.<br />

In a emperical analysis, the established framework for the analysis of an algorithm’s time and space efficiencies are measured as functions of the algorithms input size.
