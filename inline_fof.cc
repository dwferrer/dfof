//general purpose FoF code for any set of vertices
//the type of the vertices is T, and the functions
//inline int adjacent(T &a, T&b, FLOAT ll2);
//must be defined for T
//

struct Group{{
    {FLOAT} * x;
    int np;
}}



//the square distance between two vectors
inline float d2({FLOAT} * x1, {FLOAT} * x2){{
    {FLOAT} rv = 0;
    for(int i = 0; i < {VEC_SIZE}; i++) rv+=(x1[i]-x2[i])*(x1[i] -x2[i]);
    return rv;
}}

//brute-force n*m search to see if two groups are linked
inline int adjacent(Group *a,Group *n, {FLOAT} b2){{
    for(std::list<{FLOAT}>::iterator 
    for(int i = 0; i < a->np; i++){{
        for(int j = 0; j < b->np; j++){{
            if (d2(a->x[i],b->x[j]) <= b2) return 1;
        }}
    }}
    return 0;
}}

//standard Nd fof adjacency
inline int adjacent({FLOAT} * a, {FLOAT} * b, {FLOAT} b2){{
    if (d2(a,b) <= b2) return 1;
    return 0;
}}

//adjacency for lists of groups
inline int adjacent(std::list<Group> *a, std::list<Group> *b, {FLOAT} b2){{
    for(std::list<Group>::iterator a_i = a->begin(); a_i != a->end(); ++ai){{
        for(std::list<Group>::iterator b_i = b->begin(); a_i != b->end(); ++bi){{
            for(int i = 0; i < *a_i.np; i++){{
                for(int j = 0; j < *b_i->np; j++){{
                    if (d2(a->x[i],b->x[j]) <= b2) return 1;
                }}
            }}
        }}
    }}
    return 0;
}}

//swap two vectors of length VEC_SIZE
inline void swap({FLOAT} *a,{FLOAT} *b){{
    {FLOAT}[{VEC_SIZE}] temp;
    memcpy(temp,a,sizeof({FLOAT}) *{VEC_SIZE});
    memcpy(a,b,sizeof({FLOAT}) *{VEC_SIZE});
    memcpy(b,temp,sizeof({FLOAT}) *{VEC_SIZE});
}}

//swap two Groups
inline void swap(Group *a,Group *b){{
    Group temp = *a;
    *a = *b;
    *b = temp;
}}

//swap two group lists
inline void swap(std::list<Group> *a, std::list<Group> *b){{
    std::list<Group> temp = *a;
    *a = b;
    *b = temp;
}}

template<T,n>
int fof_bruteforce(T *vertices, int N, int *group_end, int *gid, int *n_friends,{FLOAT} b2){{
    int current_id = 1;
    for(int i = 0; i < N; i++){{
        int search_idx = group_end[current_id-1];
        gid[i] = current_id;
        int friends = 0;
        int swap_idx = search_idx;
        for(int j = search_idx; j < N; j++){{
            if(adjacent(vertices+n*i,vertices+n*j,b2)){{
                friends++;
                swap(vertices+n*i,vertices+n*j);
                //swap number of friends
                int temp_nf = n_friends[j] + 1; //We need to include the particle that befriended us
                n_friends[j] = n_friends[swap_idx];
                n_f[swap_idx] = temp_nf;
                swap_idx++;
            }}
        }}
        n_friends[i] += friends;
        if(friends == 0){{
            if (i >= search_idx-1){{
                group_end[current_id] = search_idx+1;
                current_id++;
            }}
        }}
        else group_end[current_id-1]+=friends;
    }}
}}

std::list<Group> * merge(std::list<Group> * groups, int N,{FLOAT} b2, int &N_new){{

    int * merge_end = new int[N];
    memset(merge_end,N*sizeof(int),0);
    int * gid = new int[N];
    memset(gid,N*sizeof(int),0);
    int * n_friends = new int[N];
    memset(n_friends,N*sizeof(int),0);

    N_new = fof_bruteforce<std::list<Group>,1>(groups, N,group_end,gid,n_friends,b2);

    std::list<Group> * mergeset = std::list<Group>[N_new];
    
    int j =0;
    for(int i = 0; i < N; i++){{
        mergeset[gid[i]].splice(mergeset[gid[i]].end(),groups[i]);
    }}

    delete merge_end;
    delete gid;
    delete nfriends;
    return mergeset;
}}
