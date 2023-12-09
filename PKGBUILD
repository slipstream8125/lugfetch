pkgname="lugfetch"
pkgver='1.0.0'
pkgrel='1'
pkgdesc="Custom fetch command made in C and Shell by LUGVITC"
arch=("x86_64")
source=("lugfetch.cpp")
depends=("gcc")
sha512sums=("SKIP")
license=("custom")
package(){
	g++ lugfetch.cpp -o lugfetch
	sudo cp lugfetch /usr/bin/lugfetch
	chmod +x /usr/bin/lugfetch
}
