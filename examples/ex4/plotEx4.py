import numpy as np
import matplotlib.pyplot as plt
import readFile as r

qK1=r.readFile("q_outK1.txt")
qtK1=r.readFile("qt_outK1.txt")
qttK1=r.readFile("qtt_outK1.txt")
qK2=r.readFile("q_outK2.txt")
qtK2=r.readFile("qt_outK2.txt")
qttK2=r.readFile("qtt_outK2.txt")
qK4=r.readFile("q_outK4.txt")
qtK4=r.readFile("qt_outK4.txt")
qttK4=r.readFile("qtt_outK4.txt")


fig=plt.figure(1)

plt.subplot(211)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\dot{\theta}(rad/s)$',fontsize=15)
plt.title('Velocidade Angular Manivela')
plt.plot(qtK1[:,0],qtK1[:,6],linewidth=1.7)
plt.plot(qtK2[:,0],qtK2[:,6],linewidth=1.7)
plt.plot(qtK4[:,0],qtK4[:,6],linewidth=1.7)
plt.legend(['K=1','K=2','K=4'],loc='best')

plt.subplot(212)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\ddot{\theta}(rad/s^2)$',fontsize=15)
plt.title('Aceleracao Angular Manivela')
plt.plot(qttK1[:,0],qttK1[:,6],linewidth=1.7)
plt.plot(qttK2[:,0],qttK2[:,6],linewidth=1.7)
plt.plot(qttK4[:,0],qttK4[:,6],linewidth=1.7)
plt.legend(['K=1','K=2','K=4'],loc='best')



fig=plt.figure(2)


plt.subplot(211)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$velocidade(m/s)$',fontsize=15)
plt.title('Velocidade Centro Cursor')
plt.plot(qtK1[:,0],qtK1[:,10],linewidth=1.7)
plt.plot(qtK2[:,0],qtK2[:,10],linewidth=1.7)
plt.plot(qtK4[:,0],qtK4[:,10],linewidth=1.7)
plt.legend(['K=1','K=2','K=4'],loc='best')

plt.subplot(212)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$aceleracao(m/s^2)$',fontsize=15)
plt.title('Aceleracao Centro Cursor')
plt.plot(qttK1[:,0],qttK1[:,10],linewidth=1.7)
plt.plot(qttK2[:,0],qttK2[:,10],linewidth=1.7)
plt.plot(qttK4[:,0],qttK4[:,10],linewidth=1.7)
plt.legend(['K=1','K=2','K=4'],loc='best')

plt.show()
