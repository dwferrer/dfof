#A simple test of an idea for a friends of friends algorithm

import numpy as np
from scipy.weave.converters import c_spec
import scipy.weave as weave

def in_box(x,b_h,b_l):
    return np.all((x < b_h),1,keepdims=True) & np.all(x >= b_l,1,keepdims=True)

def is_friend(x,x_s,l):
    test = np.linalg.norm(x_s-x,axis = 1) < l
    if not np.any(test):
        return None
    return np.where(test)[0]

def swap_to_front(data,idx,start):
    assert(np.all(idx >= start))
    codefile = open("inline_swap.cc","r")
    code = codefile.read().format(DTYPE =c_spec.num_to_c_types[data.dtype.char],VEC_SIZE = data.shape[1])
    idx = np.ascontiguousarray(idx,dtype = np.uint64)
    weave.inline(code,["data","idx","start"],verbose=2,headers=["<algorithm>","\"tbb/parallel_sort.h\"","<omp.h>"],libraries =["tbb"],extra_compile_args = ["-fopenmp"])

def fof_basic(x,b=.2):
    N = x.shape[0]
    l = b/N**(1.0/3)
    print("l = {}".format(l))
    group_end = [0]
    current_id = 1
    gid = np.zeros(N,dtype = np.int64) + np.iinfo(np.int64).max
    n_friends = np.zeros((N,1),dtype = np.int64)
    for i_active in range(N):
        x0 = x[i_active,:]
        search_idx = group_end[-1]
        gid[i_active] = current_id
        f_idx = None
        if search_idx < N:
            f_idx = is_friend(x0,x[search_idx:,:],l)
        if f_idx is None:
            if i_active == search_idx -1:
                current_id +=1
                group_end.append(search_idx + 1)
            continue
        f_idx +=search_idx
        swap_to_front(x,f_idx,search_idx)
        swap_to_front(n_friends,f_idx,search_idx)

        n_friends[search_idx:search_idx+len(f_idx),0] += 1
        n_friends[i_active,0] += len(f_idx)

        group_end[-1] += len(f_idx)

    gid[n_friends[:,0] == 0] = 0

    return np.array(group_end),gid,n_friends[:,0]

def fof_basic_inline(x,b=.2,min_np = 8):
    N = x.shape[0]
    l = b/N**(1.0/3)
    print("l = {}".format(l))
    group_end = np.zeros(N+1,dtype = np.int64)
    current_id = 1
    gid = np.zeros(N,dtype = np.int64) + np.iinfo(np.int64).max
    n_friends = np.zeros(N,dtype = np.int64)

    codefile = open("inline_basic_fof.cc","r")
    code = codefile.read().format(FLOAT =c_spec.num_to_c_types[x.dtype.char],VEC_SIZE = x.shape[1])
    last_id = weave.inline(code,["x","l","group_end","current_id","gid","n_friends"],verbose=2,
            headers=["<algorithm>","\"tbb/parallel_sort.h\"", "<omp.h>"],
            libraries =["tbb"],extra_compile_args = ["-fopenmp"])
    group_end = group_end[:last_id]
    gid[n_friends == 0] = 0

    return group_end,gid,n_friends

import matplotlib.pyplot as p
import time

def test_fof(N_halos, N_field,halo_np = 50):
    #make the field
    x = np.random.random_sample(size = (N_field,3)) - .5

    halos = np.random.poisson(halo_np,N_halos)

    for np_halo in halos:
        scale = np.random.sample()*2.0/N_halos**(1/3)
        center = np.random.sample((1,3)) -.5
        m = np.random.sample((np_halo))+.00000001
        r = (m**(-2/3) -1)**(-1/2)
        theta = np.random.sample((np_halo)) *2*np.pi
        phi = np.random.sample((np_halo))*np.pi
        x_h = np.concatenate([(r*np.cos(theta)*np.cos(phi))[:,None],(r*np.sin(theta)*np.cos(phi))[:,None],(r*np.sin(phi))[:,None]],axis = 1) * scale+center
        x = np.append(x,x_h,axis = 0)

    x_c = x.copy()
    start = time.clock()
    group_ends,gid,n_friends = fof_basic(x)
    end = time.clock()

    start_c = time.clock()
    group_ends_c,gid_c,n_friends_c = fof_basic_inline(x_c)
    end_c = time.clock()

    same = np.all(group_ends == group_ends_c)
    print ("Same: {}".format(same))
    if not same:
        print("Python: ",group_ends[:10])
        print("Inline: ",group_ends_c[:10])

    #in_group = gid != 0
    #p.scatter(x[in_group,0],x[in_group,1],c = gid[in_group],linewidth=0)
    #no_group = gid==0
    #p.scatter(x[no_group,0],x[no_group,1],c = "white")

    #p.xlabel("x")
    #p.ylabel("y")
    #p.xlim(-.5,.5)
    #p.ylim(-.5,.5)
    #p.figure()
    #p.hist(n_friends,log=1)
    #p.show()


    print ("Python: Time: {} s for {} particles".format(end-start,x.shape[0]))
    print ("Inline: Time: {} s for {} particles".format(end_c-start_c,x.shape[0]))
    return end -start,x.shape[0]

if __name__ == "__main__":
    test_fof(1000)






