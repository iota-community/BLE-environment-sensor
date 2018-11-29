PKG_NAME=iota-wallet
PKG_URL=https://github.com/embedded-iota/micro-light-wallet
PKG_VERSION=c9e1c2d8221c7d204608f6a7732ff30c0e0359eb
PKG_LICENSE=MIT

.PHONY: all

RIOT_CFLAGS = $(INCLUDES)

TOOLCHAIN_FILE=$(PKG_BUILDDIR)/xcompile-toolchain.cmake

all: $(PKG_BUILDDIR)/src/Makefile
	$(MAKE) -C $(PKG_BUILDDIR) && \
	cp $(PKG_BUILDDIR)/libiota_wallet.a $(BINDIR)/iota-wallet.a

$(PKG_BUILDDIR)/src/Makefile: $(TOOLCHAIN_FILE)
	cd $(PKG_BUILDDIR) && \
	make -e CFLAGS="$(RIOT_CFLAGS)" lib

$(TOOLCHAIN_FILE): git-download
	$(RIOTTOOLS)/cmake/generate-xcompile-toolchain.sh > $(TOOLCHAIN_FILE)

include $(RIOTBASE)/pkg/pkg.mk
