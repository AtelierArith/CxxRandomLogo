module CxxRandomLogo

module MyCxxInterface

using Libdl
using CxxWrap

@wrapmodule(() -> joinpath(pkgdir(@__MODULE__), "deps/build/lib/libjl_app.$(dlext)"))

function __init__()
	@initcxx
end

end # module MyCxxInterface

using .MyCxxInterface

using ImageCore
using Colors

function draw()
	N = 10000
	H = 368
	W = 368
	xs = zeros(N)
	ys = zeros(N)
	MyCxxInterface.generate_points!(xs, ys)
	mx, Mx = extrema(xs)
	my, My = extrema(ys)
	@. xs = (W - 5 - 5) * (xs - mx)/(Mx - mx) + 5
	@. ys = (H - 5 - 5) * (ys - my)/(My - my) + 5

	c = rand((Colors.JULIA_LOGO_COLORS.red, Colors.JULIA_LOGO_COLORS.green, Colors.JULIA_LOGO_COLORS.blue, Colors.JULIA_LOGO_COLORS.purple))

	canvas = zeros(RGB{N0f8}, H, W)
	for (x, y) in zip(xs, ys)
		iy = floor(Int, y)
		ix = floor(Int, x)
		canvas[iy, ix] = c
	end
	canvas
end

end # module CxxRandomLogo
