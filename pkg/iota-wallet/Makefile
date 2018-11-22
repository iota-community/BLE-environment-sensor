PKG_NAME=iota-wallet
PKG_URL=https://github.com/embedded-iota/micro-light-wallet
PKG_VERSION=c29b43200e5b3c451aa232224228535be54c8c42
PKG_LICENSE=MIT

.PHONY: all

RIOT_CFLAGS = $(INCLUDES)

TOOLCHAIN_FILE=$(PKG_BUILDDIR)/xcompile-toolchain.cmake

all: $(PKG_BUILDDIR)/src/Makefile
	$(MAKE) -C $(PKG_BUILDDIR) && \
	cp $(PKG_BUILDDIR)/libiota_wallet.a $(BINDIR)/iota-wallet.a

$(PKG_BUILDDIR)/src/Makefile: $(TOOLCHAIN_FILE)
	cd $(PKG_BUILDDIR) && \
	cmake -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN_FILE) \
		  -CMAKE_C_FLAGS="$(RIOT_CFLAGS)" .

$(TOOLCHAIN_FILE): git-download
	$(RIOTTOOLS)/cmake/generate-xcompile-toolchain.sh > $(TOOLCHAIN_FILE)

include $(RIOTBASE)/pkg/pkg.mk
