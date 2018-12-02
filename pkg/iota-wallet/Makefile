PKG_NAME=iota-wallet
PKG_URL=https://github.com/embedded-iota/micro-light-wallet
PKG_VERSION=9a8936fb28aef07e81163b0149e8069881d5a3c9
PKG_LICENSE=MIT

.PHONY: all

RIOT_CFLAGS = $(INCLUDES) -std=c99

TOOLCHAIN_FILE=$(PKG_BUILDDIR)/xcompile-toolchain.cmake

all: $(PKG_BUILDDIR)/src/Makefile
	$(MAKE) -C $(PKG_BUILDDIR) && \
	cp $(PKG_BUILDDIR)/build/libiota_wallet.a $(BINDIR)/iota-wallet.a

$(PKG_BUILDDIR)/src/Makefile: $(TOOLCHAIN_FILE)
	cd $(PKG_BUILDDIR) && \
	mkdir -p build && \
	make -e CFLAGS+="$(RIOT_CFLAGS)" lib

$(TOOLCHAIN_FILE): git-download
	$(RIOTTOOLS)/cmake/generate-xcompile-toolchain.sh > $(TOOLCHAIN_FILE)

include $(RIOTBASE)/pkg/pkg.mk
