#include <bits/stdc++.h>
using namespace std;
class SegmentTree{
    public:
    vector<int>seg;
    SegmentTree(int n){
        seg.resize(4*n+1);
    }
    void buildTree(int ind,int low,int high,vector<int>& arr){
        if(low==high){
            seg[ind]=arr[low];
            return;
        }
        int mid=(low+high)/2;
        buildTree(2*ind+1,low,mid,arr);
        buildTree(2*ind+2,mid+1,high,arr);
        seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
    }
    int query(int ind,int low,int high,int l,int r){
        // No overlap
        // l r low high OR low high l r
        if(r<low || l>high) return INT_MAX;
        // Complete overlap
        // l low high r
        if(l<=low && high<=r) return seg[ind];

        // Partial overlap
        int mid=(low+high)/2;
        int left=query(2*ind+1,low,mid,l,r);
        int right=query(2*ind+2,mid+1,high,l,r);
        return min(left,right);
    }
    void update(int ind,int low,int high,int i,int val){
        if(low==high){
            seg[ind]=val;
            return;
        }
        int mid=(low+high)/2;
        if(i<=mid) update(2*ind+1,low,mid,i,val);
        else update(2*ind+2,mid+1,high,i,val);
        seg[ind]=min(seg[2*ind+1],seg[2*ind+2]);
    }
};

void solve(){
    int n;
    cout<<"Enter number of elements in array\n";
    cin>>n;
    cout<<"Enter elements of array\n";
    vector<int> arr(n);
    for(int i=0;i<n;i++) cin>>arr[i];
    SegmentTree st(n);
    st.buildTree(0,0,n-1,arr);
    int q;
    cout<<"Enter number of queries\n";
    cin>>q;
    cout<<"Enter queries (type l r)\n";
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int l,r;
            cin>>l>>r;
            cout<<st.query(0,0,n-1,l,r)<<"\n";
        }else{
            int idx,val;
            cin>>idx>>val;
            arr[idx]=val;
            st.update(0,0,n-1,idx,val);
        }
    }
}
void solve2(){
    // In this we try to build 2 segment trees
    // and then we will try to answer the queries
    // 1-> find min in range l1 r1 for seg1 and l2 r2 for seg2
    // 2-> in this we will take array type and index and value and call the update query
    // So for this we need to create a class of segment tree as we need to call all these functions
    // again and again for both the segment trees
    int n1,n2;
    cout<<"Enter number of elements in array 1\n";
    cin>>n1;
    cout<<"Enter elements of array 1\n";
    vector<int> arr1(n1);
    for(int i=0;i<n1;i++) cin>>arr1[i];
    cout<<"Enter number of elements in array 2\n";
    cin>>n2;
    cout<<"Enter elements of array 2\n";
    vector<int> arr2(n2);
    for(int i=0;i<n2;i++) cin>>arr2[i];
    SegmentTree st1(n1);
    SegmentTree st2(n2);
    st1.buildTree(0,0,n1-1,arr1);
    st2.buildTree(0,0,n2-1,arr2);
    int q;
    cout<<"Enter number of queries\n";
    cin>>q;
    cout<<"Enter queries (type l1 r1 l2 r2 for type 1 and type arrType idx val for type 2)\n";
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int l1,r1,l2,r2;
            cin>>l1>>r1>>l2>>r2;
            cout<<min(st1.query(0,0,n1-1,l1,r1),st2.query(0,0,n2-1,l2,r2))<<"\n";
        }else{
            int arrType,idx,val;
            cin>>arrType>>idx>>val;
            if(arrType==1){
                arr1[idx]=val;
                st1.update(0,0,n1-1,idx,val);
            }else{
                arr2[idx]=val;
                st2.update(0,0,n2-1,idx,val);
            }
        }
    }
}

int main()
{
    // solve();
    solve2();
    return 0;

}