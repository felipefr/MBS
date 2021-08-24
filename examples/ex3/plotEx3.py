import numpy as np
import matplotlib.pyplot as plt
import readFile as r

q50=r.readFile("q_out50.txt")
qt50=r.readFile("qt_out50.txt")
q100=r.readFile("q_out100.txt")
qt100=r.readFile("qt_out100.txt")
q200=r.readFile("q_out200.txt")
qt200=r.readFile("qt_out200.txt")

fig=plt.figure(1)

plt.subplot(211)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\theta(rad)$',fontsize=15)
plt.title('Deslocamento Angulares Manivela')
plt.plot(q50[:,0],q50[:,6]%(2*np.pi),linewidth=1.7)
plt.plot(q100[:,0],q100[:,6]%(2*np.pi),linewidth=1.7)
plt.plot(q200[:,0],q200[:,6]%(2*np.pi),linewidth=1.7)
plt.legend(['T=50 Nm','T=100 Nm','T=200 Nm'],loc='best')

plt.subplot(212)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\dot{\theta}(rad/s)$',fontsize=15)
plt.title('Velocidade Angular Manivela')
plt.plot(qt50[:,0],qt50[:,6],linewidth=1.7)
plt.plot(qt100[:,0],qt100[:,6],linewidth=1.7)
plt.plot(qt200[:,0],qt200[:,6],linewidth=1.7)
plt.legend(['T=50 Nm','T=100 Nm','T=200 Nm'],loc='best')



fig=plt.figure(2)

plt.subplot(211)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$deslocamento(m)$',fontsize=15)
plt.title('Centro Cursor')
plt.plot(q50[:,0],q50[:,10],linewidth=1.7)
plt.plot(q100[:,0],q100[:,10],linewidth=1.7)
plt.plot(q200[:,0],q200[:,10],linewidth=1.7)
plt.legend(['T=50 Nm','T=100 Nm','T=200 Nm'],loc='best')

plt.subplot(212)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$velocidade(m/s)$',fontsize=15)
plt.title('Velocidade Centro Cursor')
plt.plot(qt50[:,0],qt50[:,10],linewidth=1.7)
plt.plot(qt100[:,0],qt100[:,10],linewidth=1.7)
plt.plot(qt200[:,0],qt200[:,10],linewidth=1.7)
plt.legend(['T=50 Nm','T=100 Nm','T=200 Nm'],loc='best')

plt.show()
