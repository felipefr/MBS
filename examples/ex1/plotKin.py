import numpy as np
import matplotlib.pyplot as plt
import readFile as r

q=r.readFile("q_out.txt")
qt=r.readFile("qt_out.txt")
qtt=r.readFile("qtt_out.txt")

fig=plt.figure(1)

plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\dot{\theta}(rad/s)$',fontsize=15)
plt.plot(qt[:,0],qt[:,6],linewidth=1.7)
plt.plot(qt[:,0],qt[:,9],linewidth=1.7)
plt.plot(qt[:,0],qt[:,12],linewidth=1.7)
plt.legend(['manivela','biela','cursor'],loc='best')

fig=plt.figure(2)

plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\dot{R}(m/s)$',fontsize=15)
plt.plot(qt[:,0],qt[:,10],linewidth=1.7)
plt.plot(qt[:,0],qt[:,11],linewidth=1.7)
plt.legend([r'$\dot{R_x}$', r'$\dot{R_y}$'],loc='best')

fig=plt.figure(3)

plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\ddot{\theta}(rad/s^2)$',fontsize=15)
plt.plot(qtt[:,0],qtt[:,6],linewidth=1.7)
plt.plot(qtt[:,0],qtt[:,9],linewidth=1.7)
plt.plot(qtt[:,0],qtt[:,12],linewidth=1.7)
plt.legend(['manivela','biela','cursor'],loc='best')

fig=plt.figure(4)

plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\ddot{R}(m/s^2)$',fontsize=15)
plt.plot(qtt[:,0],qtt[:,10],linewidth=1.7)
plt.plot(qtt[:,0],qtt[:,11],linewidth=1.7)
plt.legend([r'$\ddot{R_x}$', r'$\ddot{R_y}$'],loc='best')


plt.show()
