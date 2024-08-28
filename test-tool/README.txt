To build the fake-BGP:

      1. install build-essential compiler
      
          sudo apt-get install build-essential
      
      2. install lemon library:
       
          cd test-tool/fakeBGP/lemon/lemon-1.2.4
          ./configure
          make
          make check
          make install
      
      3. compile the fake-BGP

         cd test-tool/fakeBGP/linux
         make

      4. to start the fake-BGP, run:

         sudo ./fakeBGP <file .lgf>
