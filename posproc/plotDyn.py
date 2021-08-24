import numpy as np
import matplotlib.pyplot as plt
import readFile as r

Qe=r.readFile("Qe_out.txt")
Qc=r.readFile("Qc_out.txt")

fig=plt.figure(2)

plt.subplot(221)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\omega(rad)$',fontsize=15)
plt.title('deslocamento angular manivela')
plt.plot(Qe[:,0],Qe[:,6])

plt.subplot(222)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\omega(rad)$',fontsize=15)
plt.title('deslocamento angular biela')
plt.grid()
plt.plot(Qe[:,0],Qe[:,9])

plt.subplot(223)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\omega(rad/s)$',fontsize=15)
plt.title('velocidade angular manivela(rad/s)')
plt.grid()
plt.plot(Qc[:,0],Qc[:,6])

plt.subplot(224)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\omega(rad/s)$',fontsize=15)
plt.title('velocidade angular biela')
plt.grid()
plt.plot(Qc[:,0],Qc[:,9])


plt.show()
