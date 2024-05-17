#!/bin/sh

versions(){
    echo 16.3-alpine3.19
    echo 15.7-alpine3.19
    echo 14.12-alpine3.19
    echo 13.15-alpine3.19
    echo 12.19-alpine3.19
}

template=./Dockerfile.template

versions | while read ver; do
  filename=Dockerfile.${ver}
  cat "${template}" |
    sed \
      -e "s,__POSTGRESQL_VERSION__,${ver}," |
    cat > "${filename}"
done
