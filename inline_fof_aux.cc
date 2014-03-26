//Auxillary methods for multi-level FoF. This file is designed to be compliled inline by Scipy
//The following substitutions must be made
//VEC_SIZE: length of vectors you will be performing FoF on
//FLOAT: datatype of vector.

#include <vector>
#include <algorithm>

//the square distance between two vectors
inline float d2({FLOAT} * x1, {FLOAT} * x2){{
    {FLOAT} rv = 0;
    for(int i = 0; i < {VEC_SIZE}; i++) rv+=(x1[i]-x2[i])*(x1[i] -x2[i]);
    return rv;
}}

//check if a vector is in the bounding box given by two vectors
inline bool in_box({FLOAT} * x, {FLOAT} * bbox_h, {FLOAT} * bbox_l){{
    bool rv = true;
    for(int i = 0; i < {VEC_SIZE} i++) rv = rv && (x[i] >= bbox_l[i] && x[i] <= bbox_h[i]);
}}

//swap two vectors of length VEC_SIZE
inline void swap({FLOAT} *a,{FLOAT} *b){{
    {FLOAT}[{VEC_SIZE}] temp;
    memcpy(temp,a,sizeof({FLOAT}) *{VEC_SIZE});
    memcpy(a,b,sizeof({FLOAT}) *{VEC_SIZE});
    memcpy(b,temp,sizeof({FLOAT}) *{VEC_SIZE});
}}

//a struct to contain a set of groups from one level of the group finding hirearchy
struct GroupSet{{
    int *g_np;
    int *g_start;
    int length;
    {FLOAT} *x;
    int *gid;
    int set_np;
}}

//brute-force n*m search to see if two groups are linked
inline int is_linked(GroupSet &a,GroupSet &b,int gn_a , int gn_b, {FLOAT} b2){{
    for(int i = a.g_start[gn_a]; i < a.g_np[gn_a]; i++){{
        for(int j = b.g_start[gn_b]; j < b.g_np[gn_b]; j++){{
            if (d2(a.x[gn_a],b.x[gn_b]) return 1;
        }}
    }}
    return 0;
}}

//construct a table of group mergers of the form
//(id_a<->id_b)
std::list<std::array<int,2>> build_merger_table(GroupSet a,GroupSet b, {FLOAT} b2)
{{
    std::list<std::array<int,2>> mergers;
    for(int gn_a = 0; gn_a < a.length; gn_a++){{
        for(int gn_b = 0; gn_b < b.length; gn_b++){{
            if (is_linked(a,b,gn_a,gn_b,b2){{
                std::array<int,2> ab; ab[0] = gn_a; ab[1] = gn_b;
                mergers.push_back(ab);
                }}
        }}
    }}
    return mergers;
}}

bool mt_comp_left(std::array<int,2> &a,std::array<int,2> &b){{
    if (a[0] == b[0]) return a[1]<b[1];
        return a[0] < b[0];
}}

bool mt_comp_right(std::array<int,2> &a,std::array<int,2> &b){{
    if (a[1] == b[1]) return a[0]<b[0];
        return a[1] < b[1];
}}

//we merge in two passes
void merge(GroupSet &a,GroupSet &b, std::list<std::vector<int,2>> merger_table){{
    
    std::sort(merge_table,merge_table+merge_table.size,mt_comp_left);
    //std::list<std::list<int>> groups;
    
    int * remap_a = new int[a.length];
    int * remap_b = new int[b.length];

    for(int i = 0; i < a.length; i++) remap_a = -1;
    for(int i = 0; i < b.length; i++) remap_b = -1;

    int gid_new = a.length + b.length;

    for(std::list<std::vector<int,2>>::iterator x = mergers.begin(); x != mergers.end() ++x){{
        int i_a = *x[0];
        int i_b = *x[1];
        
        if (remap_b[i_b] == -1) remap_b[i_b] = i_a;
        else{{
            if (remap_a[i_a] == -1){{
                remap_a[i_a] = remap_b[i_b];
                remap_bp
            }}
        }}
        
    }}

    delete[] remap_a;
    delete[] remap_b;
}}



