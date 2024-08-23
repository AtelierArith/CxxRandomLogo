module CxxRandomLogoWrapper

export W, W!, b, b!, transform, Affine

using CxxWrap
using CxxWrap: CxxWrapCore

using EasyEigenInterface

using Libdl: dlext, Libdl

@wrapmodule(()->"$(@__DIR__)/../../build/CxxRandomLogoWrapper/deps/libjlCxxRandomLogoWrapper.$(dlext)")

function Affine(W::AbstractMatrix, b::AbstractVector)
    Affine(Matrix2d(W), Vector2d(b))
end

function __init__()
    @initcxx
end

end #module
