# 7300_Project
CSC 7300 Project

Project prompt:

The project will involve creating an FM-index (Ferragina and Manzini) based on Burrows-Wheeler Transform (BWT) of the text. You will do in groups of 4. You will experiment with the block-size parameter and obtain space-time trade-offs for various data sets from pizzachili corpus. Total 20 points.

Step 1. Given a text T, construct it suffix array SA using DC3 algorithm of Karkainnen and Sanders (covered in class). This should be O(n). If you use any other simpler algorithm which has higher complexity - your point deduction will be 2 points.

Step 2. From the suffix array now create BWT. This is just direct and straightforward.

Step 3. Construct a wavelet tree over the BWT. At each node of Wavelet tree is the bit-vector count (or rank-select) data structure. For this bitvector queries, you can divide the bit-vector into blocks of size b and then at every block boundaries maintain the explicit count for number of 1 encountered until that point in the bit-vector.

Your main operation to implement on a bitvector is rank1(i) = count the number of 1s in B[1...i]. Similarly for counting 0s - rank0(i). To do these queries, you use blocking. We explicitly maintain rank1(i) results for values of i which are multiple of b. While doing query rank1(k), we refer to rank1(i) where i is the closest multiple of b - smaller than k. and then count the additional 1 bits in the range B[i+1...k] by 'walking' through that part of the bit-vector.

Trade-off here is that if b is small then we save time during the 'walk' and it is faster. But then we have to maintain a lot more explicit answers (at block boundaries).

(2 points deduction) if your bit-vector - is not a 'packed' array. That is if you are using an integer array cell to store a single bit (that is 32 times more space). You can still use it and account for the space 'logically' by counting it as 1 bit. Ideally, you should use and array of unsigned int. and then each entry of the array stores 32 bits (interpreted as unsigned int).



Step 4. Create a query algorithm for the wavelet tree - which in turn uses query algorithm for bit-vector.

Hack: for 3 points deduction - do not construct a wavelet tree. Just maintaing explicit count structure on BWT by maintaining the counts of "each" alphabet at every block boundary of the BWT vector. So no need to go to bit-vector level.

Step 5. Use the wavelet tree to implement 'backward' pattern matching using FM-index. Your query algorithm (which takes query pattern P as an input) needs to return only the count of how many times the pattern P occurs in the text T. (You do not have to locate the occurrences).

You have to submit a report by December 3rd on Moodle. The report will describe your methods and will have space time trade-offs you achieve by tweaking b - for at least 3 data sets. The data sets can be obtained from pizza chili corpus.

http://pizzachili.dcc.uchile.cl/texts.html

https://calcoolator.eu/burrows-wheeler-transform-encoder-decoder-

 You'll also submit your code along with output (however, I will not be running it - I will do eye-inspection only.

EXTRA: apply MTF move-to-front compression on BWT and find out how much compression it achieves. (Extra part will be needed if your group has 5 members - prior permission of instructor required.)


