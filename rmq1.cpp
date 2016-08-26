// solution to Help Ashu hackerearth
// https://www.hackerearth.com/problem/algorithm/help-ashu-1/description/
#include <bits/stdc++.h>
using namespace std;

long Tree[4*100055],A[100055];

// Building a segment tree. Remember that a segtree has a static, we cannot update
// the structure of the segment tree.
// Complexity:O(n)

void build(int node, int start, int end)
{

  if (start==end)
  {
  	Tree[node]=A[start];
  	return;
  }
  int mid=(start+end)/2;
  build(2*node,start,mid);
  build(2*node+1,mid+1,end);

  Tree[node]=Tree[2*node]+Tree[2*node+1];

}

// update the built segtree 
// Complexity: O(log(n))
void update(int node, int start, int end, int indx, int val)
{
   if(start==end)
   {
   	 Tree[node]=val;
   	 A[indx]=val;
   	 return ;
   }
  int mid = (start+end)/2;
  if(indx>=start and indx<=mid)
  	update(2*node,start,mid,indx,val);
  
  if(indx>=mid+1 and indx<=end)
  	update(2*node+1,mid+1,end,indx,val);
   
  Tree[node] = Tree[2*node]+Tree[2*node+1]; 
}

int query(int node,int start,int end,int le,int ri)
{ 
	// if range represented by the 'node' is completely outside the
	// range of [le,ri]  i.e. 
  // start.....end.....le....ri   or
  // le.....ri....start.....end
 	if(end<le or start>ri)
		return 0;
	// if range represented by the 'node' is completely inside the 
	// range of [le,ri] .i.e.
  //  le....start...end....ri  
	else if( start>=le and end<=ri )
		return Tree[node];
  // if [start,end] is partially inside and partially outside the 
  // range of [le,ri]
	int mid	= (start+end)/2;
	//  query on left child
	int ans1 = (query(2*node, start, mid, le, ri ));

	// query on right child
	int ans2 = (query(2*node+1 , mid+1, end ,le, ri ));

	return ans2+ans1;
}


int main()
{
   int n,i ,j ,k ,q ,le,ri,idx,val;
   cin>>n;
   for(i=1;i<=n;i++)
      {cin>>A[i];A[i]%=2;}
   build(1,1,n);
   cin>>q;
   int ch;
   while(q--)
   {
      cin>>ch;
      if(ch==0)
         {cin>>idx>>val;update(1,1,n,idx,val%2);}
      else
      {   cin>>le>>ri;
         if(ch==1)
         cout<<(ri-le+1)-query(1,1,n,le,ri);
         else
            cout<<query(1,1,n,le,ri);
         cout<<endl;
      }
      
      
   }
 
   return 0;
}