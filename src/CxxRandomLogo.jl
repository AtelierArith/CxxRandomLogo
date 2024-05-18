module CxxRandomLogo

using Libdl

using CxxWrap

@wrapmodule(() -> joinpath(pkgdir(@__MODULE__), "build/lib/libjl_app.$(dlext)"))

function __init__()
	@initcxx
end

end # module CxxRandomLogo
