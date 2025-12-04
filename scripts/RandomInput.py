# get random input of RVISmith: --seed, --data_length, --sequence length, --root

import random
import numpy as np

def randomSeed():
    random_uint32 = np.random.randint(0, 2**32, dtype=np.uint32)
    return hex(random_uint32)

def randomDataLength():
    random_int = random.randint(0, 1000)
    # random_int = random.randint(0, 100)
    return str(random_int)

def randomSeqLength():
    random_int = random.randint(0, 15)
    # random_int = random.randint(0, 5)
    return str(random_int)

def randomRoot():
    
    vint_type = ['vint64m1_t', 'vint64m2_t', 'vint64m4_t', 'vint64m8_t'] \
    + ['vint32m1_t', 'vint32m2_t', 'vint32m4_t', 'vint32m8_t', 'vint32mf2_t'] \
    + ['vint16m1_t', 'vint16m2_t', 'vint16m4_t', 'vint16m8_t', 'vint16mf2_t', 'vint16mf4_t'] \
    + ['vint8m1_t', 'vint8m2_t', 'vint8m4_t', 'vint8m8_t', 'vint8mf2_t', 'vint8mf4_t', 'vint8mf8_t']
    
    vuint_type = ['vuint64m1_t', 'vuint64m2_t', 'vuint64m4_t', 'vuint64m8_t'] \
    + ['vuint32m1_t', 'vuint32m2_t', 'vuint32m4_t', 'vuint32m8_t', 'vuint32mf2_t'] \
    + ['vuint16m1_t', 'vuint16m2_t', 'vuint16m4_t', 'vuint16m8_t', 'vuint16mf2_t', 'vuint16mf4_t'] \
    + ['vuint8m1_t', 'vuint8m2_t', 'vuint8m4_t', 'vuint8m8_t', 'vuint8mf2_t', 'vuint8mf4_t' ,'vuint8mf8_t']

    vfloat_type = ['vfloat64m1_t', 'vfloat64m2_t', 'vfloat64m4_t', 'vfloat64m8_t'] \
    + ['vfloat32m1_t', 'vfloat32m2_t', 'vfloat32m4_t', 'vfloat32m8_t', 'vfloat32mf2_t'] \
    + ['vfloat16m1_t', 'vfloat16m2_t', 'vfloat16m4_t', 'vfloat16m8_t', 'vfloat16mf2_t', 'vfloat16mf4_t'] \
    
    vbool_type = ['vbool1_t', 'vbool2_t', 'vbool4_t', 'vbool8_t', 'vbool16_t', 'vbool32_t', 'vbool64_t']

    types = vint_type + vuint_type + vfloat_type + vbool_type

    return random.choice(types)
