import numpy as np
import matplotlib.pyplot as plt
import readFile as r

Qe=r.readFile("Qe_out.txt")
Qc=r.readFile("Qc_out.txt")
Lm=r.readFile("Lm_out.txt")

fig=plt.figure(1)


plt.grid()
plt.ylabel(r'$F(N)$',fontsize=15)
plt.title(r'$\lambda_4$',)
plt.plot(Lm[:,0], Lm[:,4],linewidth=1.7)
a=pow(np.array(Lm[:,4]),2) + pow(np.array(Lm[:,5]),2)
#~ 
plt.grid()
plt.ylabel(r'$F(N)$',fontsize=15)
plt.title(r'$\sqrt{\lambda_4^2 + \lambda_5^2}$',)
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.plot(Lm[:,0], np.sqrt(a),linewidth=1.7)
#~ 
#~ 

plt.subplot(422)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$\lambda_5$',)
plt.plot(Lm[:,0], Lm[:,5],linewidth=1.7)

plt.subplot(423)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$\lambda_6$',)
plt.plot(Lm[:,0], Lm[:,6],linewidth=1.7)

plt.subplot(424)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$\lambda_7$',)
plt.plot(Lm[:,0], Lm[:,7],linewidth=1.7)

plt.subplot(425)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$\lambda_8$',)
plt.plot(Lm[:,0], Lm[:,8],linewidth=1.7)

plt.subplot(426)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$\lambda_9$',)
plt.plot(Lm[:,0], Lm[:,9],linewidth=1.7)

plt.subplot(427)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$Momento(Nm)$',fontsize=15)
plt.title(r'$\lambda_{10}$',)
plt.plot(Lm[:,0], Lm[:,10],linewidth=1.7)

plt.subplot(428)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$\lambda_{11}$',)
plt.plot(Lm[:,0], Lm[:,11],linewidth=1.7)


fig=plt.figure(2)


#~ 
plt.grid()
plt.ylabel(r'$F(N) / T(N m)$',fontsize=15)
plt.title(r'$Q_c^1,Q_c^2,Q_c^3,Q_c^{11}, Q_c^{12}$', fontsize=15)
#~ ####plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.plot(Qc[:,0], Qc[:,1],linewidth=1.7)

plt.subplot(422)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$Q_c^4$',fontsize=15)
plt.plot(Qc[:,0], Qc[:,4],linewidth=1.7)

plt.subplot(423)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$Q_c^5$',fontsize=15)
plt.plot(Qc[:,0], Qc[:,5],linewidth=1.7)

plt.subplot(424)
plt.grid()
plt.ylabel(r'$Momento(Nm)$',fontsize=15)
plt.title(r'$Q_c^6$',fontsize=15)
plt.plot(Qc[:,0], Qc[:,6],linewidth=1.7)

plt.subplot(425)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$Q_c^7$',fontsize=15)
plt.plot(Qc[:,0], Qc[:,7],linewidth=1.7)

plt.subplot(426)
plt.grid()
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$Q_c^8$',fontsize=15)
plt.plot(Qc[:,0], Qc[:,8],linewidth=1.7)

plt.subplot(427)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$Momento(Nm)$',fontsize=15)
plt.title(r'$Q_c^9$',fontsize=15)
plt.plot(Qc[:,0], Qc[:,2],linewidth=1.7)

plt.subplot(428)
plt.grid()
plt.xlabel(r'$tempo(s)$',fontsize=15)
plt.ylabel(r'$Forca(N)$',fontsize=15)
plt.title(r'$Q_c^{10}$',fontsize=15)
plt.plot(Qc[:,0], Qc[:,10],linewidth=1.7)


plt.show()
