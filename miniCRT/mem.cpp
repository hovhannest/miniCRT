
extern "C" void* __cdecl
memcpy(void* dest, void* src, unsigned int len)
{
    unsigned int i;
    char* char_src = (char*)src;
    char* char_dest = (char*)dest;
    for (i = 0; i < len; i++) {
        char_dest[i] = char_src[i];
    }
    return dest;
}

extern "C" void* __cdecl
memmove(void* dest, void* src, unsigned int len)
{
    unsigned int i;
    char* char_src = (char*)src;
    char* char_dest = (char*)dest;
    if (char_dest > char_src) {
        if (len == 0) {
            return dest;
        }
        for (i = len - 1; ; i--) {
            char_dest[i] = char_src[i];
            if (i == 0) break;
        }
    }
    else {
        for (i = 0; i < len; i++) {
            char_dest[i] = char_src[i];
        }
    }
    return dest;
}

extern "C" void* __cdecl
memset(void* dest, char c, unsigned int len)
{
    unsigned int i;
    unsigned int fill;
    unsigned int chunks = len / sizeof(fill);
    char* char_dest = (char*)dest;
    unsigned int* uint_dest = (unsigned int*)dest;

    //
    //  Note we go from the back to the front.  This is to 
    //  prevent newer compilers from noticing what we're doing
    //  and trying to invoke the built-in memset instead of us.
    //

    fill = (c << 24) + (c << 16) + (c << 8) + c;

    for (i = len; i > chunks * sizeof(fill); i--) {
        char_dest[i - 1] = c;
    }

    for (i = chunks; i > 0; i--) {
        uint_dest[i - 1] = fill;
    }

    return dest;
}

extern "C" int __cdecl
memcmp(const void* buf1, const void* buf2, unsigned int len)
{
    unsigned int i = 0;
    unsigned char* char_buf1 = (unsigned char*)buf1;
    unsigned char* char_buf2 = (unsigned char*)buf2;
    for (i = 0; i < len; i++) {
        if (char_buf1[i] < char_buf2[i]) {
            return -1;
        }
        else if (char_buf1[i] > char_buf2[i]) {
            return 1;
        }
    }
    return 0;
}