import numpy as np
import matplotlib.pyplot as plt
import readFile as r

q=r.readFile("q_out.txt")
qt=r.readFile("qt_out.txt")
qtt=r.readFile("qtt_out.txt")
Qe=r.readFile("Qe_out.txt")
Qc=r.readFile("Qc_out.txt")

fig=plt.figure(1)

plt.subplot(321)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\omega(rad)$',fontsize=15)
plt.title('deslocamento angular manivela')
plt.plot(q[:,0],q[:,6]%(2*np.pi))

plt.subplot(322)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\omega(rad)$',fontsize=15)
plt.title('deslocamento angular biela')
plt.grid()
plt.plot(q[:,0],q[:,9]%(2*np.pi))

plt.subplot(323)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\omega(rad/s)$',fontsize=15)
plt.title('velocidade angular manivela(rad/s)')
plt.grid()
plt.plot(qt[:,0],qt[:,6])

plt.subplot(324)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\omega(rad/s)$',fontsize=15)
plt.title('velocidade angular biela')
plt.grid()
plt.plot(qt[:,0],qt[:,9])

plt.subplot(325)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\alpha(rad/s^2)$',fontsize=15)
plt.title('aceleracao angular manivela')
plt.grid()
plt.plot(qtt[:,0],qtt[:,6])

 
plt.subplot(326)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$\alpha(rad/s^2)$',fontsize=15)
plt.title('aceleracao angular biela(rad/s^2)')
plt.grid()
plt.plot(qtt[:,0],qtt[:,9])

plt.show()
	
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
