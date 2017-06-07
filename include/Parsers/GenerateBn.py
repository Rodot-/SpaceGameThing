import struct


class prop: #asset property

	def __init__(self, value, form, name):
		self.value = value;
		self.form = form;
		self.name = name;

	def size(self):

		if (self.form == 's'):
			return len(self.value)
		else:
			return struct.calcsize(self.form)

	def getBytes(self):
		size = bytearray(struct.pack('B', self.size()))
		name = bytearray(struct.pack('c', self.name))
		if (self.form == 's'):
			value = bytearray(self.value)
		else:
			value = struct.pack(self.form, self.value)

		return name+size+value
			

class GameAsset:

	def __init__(self, texture, pos, origin, color, collidable, collisionMethod):
		self.texture = prop(texture, 's', 'T')
		self.x = prop(pos[0], '<f', 'x')
		self.y = prop(pos[1], '<f', 'y')
		self.X = prop(origin[0], '<f', 'X')
		self.Y = prop(origin[1], '<f', 'Y')
		self.R = prop(color[0], 'I', 'R')
		self.G = prop(color[1], 'I', 'G')
		self.B = prop(color[2], 'I', 'B')
		self.A = prop(color[3], 'I', 'A')
		self.collidable = prop(collidable, '?', 'c')
		self.collisionMethod = prop(collisionMethod, 'B', 'C')

	def getBytes(self):

		props = map(lambda x: x[1], filter(lambda x: not x[0].startswith('_'), self.__dict__.items()))
		ba = bytearray('\0a')+bytearray(struct.pack('B',11)) 
		for prop in props:
			ba += prop.getBytes()
		return ba
		#return bytearray('a')+bytearray(struct.pack('B',11))+sum(map(lambda x: x[1].getBytes(), filter(lambda x: not x[0].startswith('_'), self.__dict__.items())), bytearray())

class PhysAsset:

	def __init__(self, **kwargs):
		for (key, value) in kwargs.items():
			self.__dict__[key] = prop(value, '<f', key)
		self._size = len(kwargs.values())

	def getBytes(self):
		props = map(lambda x: x[1], filter(lambda x: not x[0].startswith('_'), self.__dict__.items()))
		ba = bytearray('p')+bytearray(struct.pack('B',self._size)) 
		for prop in props:
			ba += prop.getBytes()
		return ba	
		


asset = GameAsset('bin/planet.png',(95,95),(0,0),(255,123,234,150),True,1)
physobj = PhysAsset(m=0.5, x = 10, y = 20, s = 0.4, I = 0.67, Y = 10.5)
with open('test2.bn','wb') as f:
	f.write(asset.getBytes() + physobj.getBytes())
	f.write(asset.getBytes() + physobj.getBytes())


'''
header = ['ah', 'ah']
nproperties = [2, 1]
properties = [['m', 'r'], ['r']]
property_types = [['<f','<f'], ['<f']]
property_values = [[1000.0, 5.0], [20.5]]

Nitems = len(header)
ba = bytearray([])
for j in xrange(Nitems):
	ba += bytearray(header[j])
	ba += bytearray(struct.pack('B',nproperties[j]))
	props = properties[j]
	propt = property_types[j]
	propv = property_values[j]
	for i in xrange(nproperties[j]):
		ba += bytearray(struct.pack('c',props[i]))
		if propt[i] == 's':
			ba += bytearray(struct.pack('B',len(propv[i])))
			ba += bytearray(propv)
		elif propt[i].endswith('f'):
			ba += bytearray(struct.pack('B',struct.calcsize(propt[i])))
			ba += bytearray(struct.pack(propt[i], propv[i]))
with open("testFile.bn","wb") as f:
	f.write(ba)
'''

