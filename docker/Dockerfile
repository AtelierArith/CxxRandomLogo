FROM ubuntu:22.04

# Create user named jovyan which is compatible with Binder
ARG NB_USER=jovyan
ARG NB_UID=1000
ENV USER ${NB_USER}
ENV NB_UID ${NB_UID}
ENV HOME /home/${NB_USER}

RUN adduser --disabled-password \
    --gecos "Default user" \
    --uid ${NB_UID} \
    ${NB_USER}

RUN mkdir -p /workspaces/
RUN chown -R ${NB_UID} /workspaces/ ${HOME}

RUN apt-get update && apt-get install -y \
    git tig nano htop make cmake curl build-essential libeigen3-dev

USER ${NB_USER}
WORKDIR ${HOME}

RUN curl -fsSL https://install.julialang.org | sh -s -- --yes
ENV JULIA_PROJECT=@.
ENV PATH=${HOME}/.juliaup/bin:${PATH}

RUN julia -e 'using Pkg; Pkg.add(name="WrapIt", version="1.4.0")'
RUN julia -e 'using WrapIt; WrapIt.install(expanduser("~/.juliaup/bin"))'
RUN julia -e 'using Pkg; Pkg.add(name="CxxWrap", version="0.16.0")'
RUN git clone https://github.com/AtelierArith/EasyEigenInterface.jl.git && \
    cd EasyEigenInterface.jl && \
    julia --project=. -e 'using Pkg; Pkg.build()'
RUN julia -e 'using Pkg; Pkg.develop(path=expanduser("~/EasyEigenInterface.jl"))'

USER ${NB_USER}