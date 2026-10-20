# Builds the two semantic oracles, each twice (ref and UBSan):
#   O1 sid     CGEN output shipped in the SID snapshot (fetched by fetch-sid.sh)
#   O2 cgen26  regenerated from binutils' xstormy16.cpu by current CGEN (cgen26/gen)
# Outputs go to $(B) (default build/): sid-ref sid-ubsan cgen26-ref cgen26-ubsan.
B ?= build
CXX ?= g++
CC ?= gcc
OPT = -O2 -fwrapv -g0
UBSAN = -O1 -fwrapv -fsanitize=undefined -fno-sanitize-recover=undefined
WARN = -w

SID = $(B)/sid/gen
SIDSRC = $(SID)/xstormy16-sem.cxx $(SID)/xstormy16-decode.cxx
O1INC = -I. -Isid-shim -I$(SID)
O2INC = -I. -Icgen26 -Icgen26/gen -Icgen26/sim -I$(B)/cgen26

all: $(B)/sid-ref $(B)/sid-ubsan $(B)/cgen26-ref $(B)/cgen26-ubsan

$(B)/sid/.fetched: fetch-sid.sh
	./fetch-sid.sh $(B)/sid
	touch $@

$(SIDSRC): $(B)/sid/.fetched

$(B)/sid-%: driver.cxx o1-sid.cxx $(SIDSRC) sid-shim/xstormy16.h sid-shim/sid-hooks.inc xs16-case.h xs16-bus.h ub-guards.h
	$(CXX) -std=gnu++17 $(if $(filter ubsan,$*),$(UBSAN),$(OPT)) $(WARN) $(O1INC) -o $@ \
		driver.cxx o1-sid.cxx $(SIDSRC)

# The generated decoder's switch and the itype names, cut out of gen/dec.c and gen/dec.h.
$(B)/cgen26/decode-switch.inc: cgen26/gen/dec.c
	mkdir -p $(@D)
	awk '/CGEN_INSN_WORD insn = base_insn;/ { p = 1 } /^ done:/ { p = 0 } p' $< > $@
	grep -q 'XSTORMY16_INSN_X_INVALID; goto done;' $@

$(B)/cgen26/itype-names.inc: cgen26/gen/dec.h
	mkdir -p $(@D)
	awk '/^typedef enum xstormy16_insn_type/ { p = 1; next } /^}/ { p = 0 } p' $< \
		| grep -o 'XSTORMY16_INSN_[A-Z0-9_]*' | grep -v '_MAX$$' | sed 's/^XSTORMY16_INSN_\(.*\)/"\1",/' > $@

$(B)/cgen26-%.o: o2-cgen26.c cgen26/gen/sem.c cgen26/sim/sim-main.h $(B)/cgen26/decode-switch.inc $(B)/cgen26/itype-names.inc xs16-case.h xs16-bus.h ub-guards.h
	$(CC) -std=gnu11 $(if $(filter ubsan,$*),$(UBSAN),$(OPT)) $(WARN) $(O2INC) -c -o $@ o2-cgen26.c

$(B)/cgen26-%: driver.cxx $(B)/cgen26-%.o
	$(CXX) -std=gnu++17 $(if $(filter ubsan,$*),$(UBSAN),$(OPT)) $(WARN) -I. -o $@ driver.cxx $(B)/cgen26-$*.o

clean:
	rm -rf $(B)

.PHONY: all clean
.SECONDARY:
