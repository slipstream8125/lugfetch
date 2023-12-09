pkgname="lugfetch"
pkgver='1.0.0'
pkgrel='1'
pkgdesc="Custom fetch command made in C and Shell by LUGVITC"
arch=("x86_64")
source=("lugfetch.cpp")
depends=("gcc")
sha512sums=("SKIP")
license=("custom")
build() {
    cd "$srcdir/"
    g++ lugfetch.cpp -o lugfetch
}

package() {
    cd "$srcdir/"
    mkdir -p "$pkgdir/usr/bin"
    cp "$pkgname" "$pkgdir/usr/bin/"
}
