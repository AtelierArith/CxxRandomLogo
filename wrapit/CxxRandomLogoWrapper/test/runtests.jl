using Test
using CxxRandomLogoWrapper
using EasyEigenInterface

@testset "Affine" begin
    weight = [1.0 2.0; 3.0 4.0]
    bias = [1.0, 2.0]
    aff = Affine(weight, bias)
    @test W(aff) == weight
    @test b(aff) == bias
    @test transform(aff, Vector2d([1.0, 1.0])) == [4.0, 9.0]
end

@testset "Affine" begin
    weight = Matrix2d([1.0 2.0; 3.0 4.0])
    bias = Vector2d([1.0, 2.0])
    aff = Affine(weight, bias)

    @test W(aff) == weight
    @test b(aff) == bias
    @test transform(aff, Vector2d([1.0, 1.0])) == [4.0, 9.0]
end
