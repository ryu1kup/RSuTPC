      subroutine source
!
! Call LLNL Cosmic-Ray Physics (CRY) library to generate secondaries
! produced by cosmic-ray showers.
!



       use mcnp_global
       use mcnp_debug
       use mcnp_random






       implicit real(dknd) (a-h,o-z)
       implicit integer (i-n)


      integer*4 npmax
      parameter (npmax=1000)

      integer*4 pidmap(0:6)

      real*8 cry_e(npmax) ! kin. E (MeV)
      real*8 cry_x(npmax) ! x (m)
      real*8 cry_y(npmax)
      real*8 cry_z(npmax)
      real*8 cry_u(npmax)
      real*8 cry_v(npmax)
      real*8 cry_w(npmax)
      real*8 cry_t(npmax)

      integer*4 cry_init
      integer*4 cry_smp
      integer*4 cry_pid(npmax) ! particle id
      integer*4 cry_charge(npmax) ! particle charge
      integer*4 itracked(npmax) 
      integer*4 ierr
      integer*4 ifirst
      integer*4 npar
      integer*4 npartracked
      integer*4 ip,kp

! arg= CRY pid: neutron=0,proton=1,pion=2,kaon=3,muon=4,electron=5,gamma=6
! map= mcnpx pid

      data pidmap /1,9,20,22,4,3,2/

      data ifirst /1/




      save ifirst

! source cell # = idum(1)
! z pos of cosmic ray = rdum(1)

      if(ifirst.eq.1)then
        ifirst = 0
        ierr = cry_init(rang)
      endif

      icl = namchg(1,idum(1)) ! convert from user cell to internal cell #
      zzz = rdum(1) ! z start position in cm

      jsu = 0
      wgt = 1.0d0
      npa = 1

!....Copy cutoffs and importance settings from original source cell to the
! current cell
      do i=1,mipt
         elc(i)=elp(i,icl) ! elc=e-cutoffs in current cell, elp = cell dep cutoffs
         fiml(i)=fim(i,icl) ! fiml= importances in current cell, fim = cell dep importances
      enddo





    1 npar = cry_smp(cry_e,cry_x,cry_y,cry_z,cry_u,cry_v,cry_w,&
     & cry_t,cry_pid,cry_charge,npmax)


      npartracked = 0

      do 10 kp=1,npar

        erg = cry_e(kp)
        ipt = pidmap(cry_pid(kp))

! check if particle is tracked
        if(ipt .gt. mipt ) goto 10 ! MCNP can only handle n,e,photon
        if(kpt(ipt).eq.0) goto 10 ! discard particles not tracked
        if(erg.gt.emx(ipt)) goto 10 ! discard particles above max E

        npartracked = npartracked+1
        itracked(npartracked) = kp
10    continue

      if(npartracked.eq.0) goto 1
 
 
      do 20 ip=1,npartracked
        kp = itracked(ip)
 
        ipt = pidmap(cry_pid(kp))
        erg = cry_e(kp)
        jan = cry_charge(kp)

! special cases:

! neutron
        if(ipt.eq.1) jan = 1

! electron
        if(ipt.eq.3) jan = -jan

! proton
        if(ipt.eq.9) jan = -jan



        if (ipt.eq.2) then
          vel = slite
        else
          vel = slite*dsqrt(erg*(erg+2.*gpt(ipt)))/(erg+gpt(ipt))
        endif

        xxx= 100.*cry_x(kp) ! m -> cm
        yyy= 100.*cry_y(kp)

        tme= 1.e8*cry_t(kp) ! sec -> shake

        uuu= cry_u(kp)
        vvv= cry_v(kp)
        www= cry_w(kp)

        if (ip.lt.npartracked) then
           nx = 1
           paxtc(1,nx,ipt) = paxtc(1,nx,ipt) + 1
           paxtc(2,nx,ipt) = paxtc(2,nx,ipt) + wgt
           paxtc(3,nx,ipt) = paxtc(3,nx,ipt) + (wgt*erg)
           pac(kpac+ipt,1,icl) = pac(kpac+ipt,1,icl)+one
           call bankit(5)
         endif

20    continue

      return
      end
