#ifndef HELPER_H__
#define HELPER_H__

template<typename T> char* binary(T n) {
	const int bits = sizeof(T)*8;
	static char str[bits+1];
	str[bits] = 0;
	for(int i = 0; i < bits; i++) {
		str[bits-i-1] = '0' + (n & 1);
		n = n >> 1;
	}

	return str;
}

#endif /* end of include guard: HELPER_H__ */