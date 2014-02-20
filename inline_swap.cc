long long int length = Ndata[0];

{DTYPE} temp[{VEC_SIZE}];

long long int swap_idx = start;

tbb::parallel_sort(&(IDX1(0)),&(IDX1(0)) + Nidx[0]);

for (long long int i =0; i < Nidx[0]; i++){{
    memcpy(&temp,&(DATA2(IDX1(i),0)),{VEC_SIZE} *sizeof({DTYPE}));
    memcpy(&(DATA2(IDX1(i),0)),&(DATA2(swap_idx,0)),{VEC_SIZE} *sizeof({DTYPE}));
    memcpy(&(DATA2(swap_idx,0)),&temp,{VEC_SIZE} *sizeof({DTYPE}));
    swap_idx++;
}}
