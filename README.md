# Segment-Tree-Generic
A general purpose generic segment tree library


1. include SegmentTree.h
2. to construct a segment tree you need to specify the following:<br>
   a. The datatype of array and the datatype of updates for which the tree is being constructed.<br>
   b. vector for which the tree is to be constructed.<br>
   c. the default value of the datatype will be used as default value for each node.<br>
   d. a function combine that specifies how the result of left and right child of a node<br> 
        should be used to generate the value of current node.
3. Example usage:      
   int maxi(int &x,int &y){return max(x,y);}<br>
   SegmentTree <int, int> rangeMaxQueries(dataVector, maxi);<br>
   
   int sum(int x, int y){return x+y;}<br>
   SegmentTree < int > rangeSumQueries(dataVector,0,sum);<br>
  
   
solution to CSES Dynamic Range Sum Queries using segTree library : https://pastebin.com/NCYXj4TK
