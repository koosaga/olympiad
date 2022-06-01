from Crypto.Cipher import AES

def decrypt(ctext: str, key: str) -> str:
	ctext, key = bytes.fromhex(ctext), bytes.fromhex(key)
	ptext = AES.new(key, AES.MODE_CBC, IV=b"\x00"*16).decrypt(ctext)
	return ptext.hex().upper()

def encrypt(ptext: str, key: str) -> str:
	ptext, key = bytes.fromhex(ptext), bytes.fromhex(key)
	ctext = AES.new(key, AES.MODE_CBC, IV=b"\x00"*16).encrypt(ptext)
	return ctext.hex().upper()

def i2k(x):
	s = "0" * 27
	for i in range(0, 5):
		fuck = x % 16
		if fuck < 10:
			s = chr(fuck + ord('0')) + s
		else:
			s = chr(fuck - 10 + ord('A')) + s
		x >>= 4

	return s

input()
S = input()
T = input()

mp1 = {}
mp2 = {}

for i in range(0, 2**20):
	mp1[encrypt(S, i2k(i))] = i
	mp2[decrypt(T, i2k(i))] = i

for k, v in mp1.items():
	if k in mp2:
		print(i2k(mp1[k]))
		print(i2k(mp2[k]))
		break
