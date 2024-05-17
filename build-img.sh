#!/bin/sh

img=takanori-yanagitani/dir_fdw
ver=$(cat ./version.txt)
tag="${img}:${ver}"

file="./Dockerfile"
ctx="."

cores(){
    which nproc | fgrep -q nproc || return
    nproc --all
}

images(){
    docker \
        images \
        "${tag}" |
        fgrep "${img}" |
        fgrep -q "${ver}"
}

build() {
    local num_of_cpu_cores
    num_of_cpu_cores=$1
    readonly num_of_cpu_cores

	docker \
		buildx \
		build \
        --build-arg NUM_CPU_CORES=${num_of_cpu_cores:-2} \
        --progress plain \
		--file "${file}" \
        --tag "${tag}" \
		"${ctx}"
}

num_of_cores=$( cores )
num_of_cores=${num_of_cores:-2}
images || build ${num_of_cores}
