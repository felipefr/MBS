import numpy as np
import matplotlib.pyplot as plt
import readFile as r

qCent=r.readFile("q_outCent.txt")
qtCent=r.readFile("qt_outCent.txt")
qttCent=r.readFile("qtt_outCent.txt")
qExc=r.readFile("q_outExc.txt")
qtExc=r.readFile("qt_outExc.txt")
qttExc=r.readFile("qtt_outExc.txt")




fig=plt.figure(1)


plt.subplot(211)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\dot{\theta}(rad/s)$',fontsize=15)
plt.title('Velocidade Angular Manivela')
plt.plot(qtCent[:,0],qtCent[:,6],linewidth=1.7)
plt.plot(qtExc[:,0],qtExc[:,6],linewidth=1.7)
plt.legend(['Centralizado','Excentrico'],loc='best')

fig=plt.figure(2)

plt.subplot(212)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\ddot{\theta}(rad/s^2)$',fontsize=15)
plt.title('Aceleracao Angular Manivela')
plt.plot(qttCent[:,0],qttCent[:,6],linewidth=1.7)
plt.plot(qttExc[:,0],qttExc[:,6],linewidth=1.7)
plt.legend(['Centralizado','Excentrico'],loc='best')


plt.show()
