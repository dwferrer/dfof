

inline float r2(float * x){{
    float rv = 0;
    for(int i = 0; i < {VEC_SIZE}; i++) rv+=x[i];
    return rv;
}}

inline bool in_box(float * x, float * bbox_h, float * bbox_l){{
    bool rv = true;
    for(int i = 0; i < {VEC_SIZE} i++) rv = rv && (x[i] >= bbox_l[i] && x[i] <= bbox_h[i]);
}}

inline void swap(float *a,float *b){{
    float[{VEC_SIZE}] temp;
    memcpy(temp,a,sizeof({FLOAT}) *{VEC_SIZE});
    memcpy(a,b,sizeof({FLOAT}) *{VEC_SIZE});
    memcpy(b,temp,sizeof({FLOAT}) *{VEC_SIZE});
}}

int get_boundary({FLOAT} * x,int * nfriends,int np,float * bbox_h, float * bbox_l,float b){{
    int swap_idx = 0;
    for(int i = 0; i < np; i++) {{
        if (in_box(&(x[i]),bbox_h,bbox_l)){{
            swap(&(x[i]),&(x[swap_idx]));
            swap_idx++;
        }}
    }}
    return swap_idx;
}}

void merge(

