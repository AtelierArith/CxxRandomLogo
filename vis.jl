using StatsPlots
using CSV
using DataFrames

df = CSV.read("out.csv", DataFrame)
@df df scatter(:x, :y)
savefig("out.png")
