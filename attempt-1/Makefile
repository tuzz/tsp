CPPFLAGS = -I ./src \
           -I ./vendor/open-wbo \
           -I ./vendor/open-wbo/algorithms \
           -I ./vendor/open-wbo/solvers/glucose3.0 \
           -DNSPACE=Glucose \
           -Wall -Wno-parentheses -O3

LDFLAGS = -L ./vendor/open-wbo \
          -L ./vendor/open-wbo/algorithms \
          -L ./vendor/open-wbo/encodings \
          -L ./vendor/open-wbo/solvers/glucose3.0 \
          -l Alg_WBO.o \
          -l MaxSAT.o \
          -l core/Solver.o \
          -l Encoder.o \
          -l Enc_MTotalizer.o \
          -l Enc_Totalizer.o \
          -l Enc_SWC.o \
          -l Enc_Ladder.o \
          -l Enc_CNetworks.o \
          -l Encodings.o

.PHONY: test

run: src/*.cc open-wbo
	g++ $(CPPFLAGS) $(LDFLAGS) src/main.cc -o run

open-wbo:
	pushd vendor/open-wbo; make r

clean:
	pushd vendor/open-wbo; make clean; popd \
	rm -f run \
	rm -f runner
