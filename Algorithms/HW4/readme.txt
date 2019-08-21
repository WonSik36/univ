/**************************************************************************
	Algorithm Analysis(ITP) HW4

	21300691 Cheung Won Sik

	How to Compile Code to Program
	1. (on command line) gcc hw4.c -o hw4
	2. It should be compiled in windows system

	How to Execute Program
	1. (on command line) hw4.exe
	   -> It automatically use "hw4.data" to input data
	2. (on command line) hw4.exe (file_name)
	   -> use "file_name" to input data

	Input File Assumption
	1. Graph name is one alphabet character
	2. Vertex order is not matter (that will be Sorted in code)
	3. But column and row order should be same

	Return of program
	1.Array of adjacency list of given graph
	2.Discovery time and finish time of each vertex after step1 of SCC Algorithm
	3.Array of adjacency list of transpose graph after step2 of SCC Algorithm
	4.Discovery time and finish time of each vertex after step3 of SCC Algorithm
	5.SCC result

**************************************************************************/