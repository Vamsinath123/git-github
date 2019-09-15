#include <bits/stdc++.h>

using namespace std;

struct memory{    
	long long prog_no;
	long long start;
	long long len;
};

typedef list<memory>::iterator iter;

/*long long deallocate(list<memory> &l,long long p,long long ad,vector<iter> &add)  // deallcates with given character
{
	if(l.empty()) return 1;	  //list is empty
	
	for(int i=0;i<add.size();i++)
	{
		if(add[i]->start==ad)
			{
				l.erase(add[i]);
				add.erase(add.begin()+i);
				return 0;
			}
	}
	return 1;
}*/

long long allocate(list<memory> &l,long long p,long long s,long long M,vector<iter> &addvec)
{
	memory m;
	m.prog_no=p;
	m.len=s;
	if(l.empty())
	{
		if(s>M) return -1;
		m.start=0;
		l.insert(l.begin(),m);
		addvec.push_back(l.begin());  //first element inserted
		return 0;
	}

	if(l.begin()->start>=s)
	{
		m.start=0;
		l.insert(l.begin(),m);
		addvec.push_back(l.begin());
		return 0;
	}
	auto it=l.begin();
	auto it2=l.begin();
	it2++;
	for(it;it2!=l.end();it++,it2++)
	{
		if((it2)->start-(it->start+it->len)>=s)
		{
			m.start=(it->start+it->len);
			l.insert(it2,m);
			addvec.push_back(--it2);
			return m.start;
		}
	}
	if((M-(it->start+it->len)>=s))
	{
		m.start=(it->start+it->len);
		l.insert(l.end(),m);
		addvec.push_back(++it);
		return m.start;
	}
	return -1;

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	long long n;
	cin>>n;
	long long M;
	cin>>M;

	char ch;
	long long p,s,ad;
	cin>>ch;

	list<memory> l;
	vector<long long> ans;
	
	vector<vector<iter> > addvec(n);

	typedef vector<long long> tuple;
	vector<tuple> q,qu;
	tuple t(3);
	long long i=0;
	while(ch!='H')
	{
		if(ch=='A')
		{
			cin>>p>>s;
			long long res=allocate(l,p,s,M,addvec[p]);
			ans.push_back(res);
			if(res==-1)
			{
				t[0]=i;
				t[1]=p;
				t[2]=s;
				q.push_back(t);
			}
			i++;
		}

		else if(ch=='D')
		{
			cin>>p>>ad;
			//ans.push_back(deallocate(l,p,ad,addvec[p]));
			i++;
			long long res=1;
			if(addvec[p].empty()||l.empty()) res=1;
			else 
			{
				iter it1=l.begin(),it2=l.end();
				for(int a=0;a<addvec[p].size();a++)
				{
					if(addvec[p][a]->start==ad)
					{
						auto it=addvec[p][a];
						if(it!=l.begin()){
							it1=--it;
							l.erase(addvec[p][a]);
							it2=++it;
						}
						else l.erase(addvec[p][a]);
						addvec[p].erase(addvec[p].begin()+a);
						res=0;
						break;
					}
				}
				//cout<<it1->len<<" "<<it2->len<<endl;
				if(!q.empty()&&res==0)
				{
					qu=q;
					long long t=0;
					for(long long j=0;j<qu.size();j++)
					{
						long long no,le,pos;
						no=qu[j][1];
						le=qu[j][2];
						pos=qu[j][0];
						long long r;	
													//long long r=allocate(l,qu[j][1],qu[j][2],M,addvec[qu[j][1]]);
						if(it2!=l.end()){
							//cout<<"sadf";
							if((it2)->start-(it1->start+it1->len)>=le)
							{
								memory m;
								m.prog_no=no;
								m.len=le;
								m.start=(it1->start+it1->len);									
								l.insert(it2,m);
									//auto sub=--it2
								addvec[m.prog_no].push_back(--it2);
								it1=it2;
								it2++;
								r=m.start;
								
							}
							else r=-1;}
							else r=allocate(l,no,le,M,addvec[no]);

						if(r!=-1){
						q.erase(q.begin()+j-t);
						t++;
						ans[qu[j][0]]=r;}
					}
				}
			}
			ans.push_back(res);
		}

		else if(ch=='T')
		{
			cin>>p;
			if(addvec[p].empty()) ans.push_back(1);
			else
			{
				for(int a=0;a<addvec[p].size();a++)
					l.erase(addvec[p][a]);
				ans.push_back(0);
				addvec[p].resize(0);
			}

			if(!q.empty())
			{
				qu=q;
				long long t=0,ano=0;
				for(long long j=0;j<qu.size();j++)
				{
					long long no;
					no=qu[j][1];	
					if(no==p){
					q.erase(q.begin()+j-t-ano);
					t++;}
					else if(ans.back()==0){
					long long r=allocate(l,qu[j][1],qu[j][2],M,addvec[qu[j][1]]);
					if(r!=-1){
					q.erase(q.begin()+j-ano-t);
					ano++;
					ans[qu[j][0]]=r;}}
				}
			}
			i++;
		}
		cin>>ch;
	}
	for(long long i=0;i<ans.size();i++)
		cout<<ans[i]<<endl;
}