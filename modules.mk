mod_masa23_test.la: mod_masa23_test.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_masa23_test.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_masa23_test.la
