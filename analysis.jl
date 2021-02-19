import DelimitedFiles: readdlm
import Metaheuristics: PerformanceIndicators
import LinearAlgebra: norm
import Statistics: mean, median, std

IGD(A, true_pareto_front) = PerformanceIndicators.igd(A, true_pareto_front)

function get_front(fname)
    M_ = readdlm(fname, ' ')
    if size(M_, 2) == 6
        M_ = M_[:,1:5]

    elseif size(M_, 2) == 11
        M_ = M_[:,1:10]
    end
    
    return M_
end




function get_unary_metric_values(nrun, pf5, pf10)

    fname_tipo4 = "pf-approx/dtlz2-5-run$(nrun).txt"
    fname_tipo5 = "pf-approx/dtlz2-10-run$(nrun).txt"
    tipo4 = get_front(fname_tipo4)
    tipo5 = get_front(fname_tipo5)

    return [ IGD(tipo4, pf5), IGD(tipo5, pf10) ]

end

function test_and_tables(results)
    mmin = minimum(results, dims=1)
    mmax = maximum(results, dims=1)
    mmedian = median(results, dims=1)
    mmean = mean(results, dims=1)
    sstd = std(results, dims=1)

    stats = [ mmin' mmedian' mmax' ]

    println(" & Min. & Mean & Std. & Max. \\\\ \\hline")
    for i = 1:size(stats,1)
        print(join(string.( round.(stats[i,:], digits=4) ), " & "))
        println("\\\\")
    end
end



function main()
    # cambiar a 10
    fname_true = "pf-true/zcat3-3.txt"
    pf10 = readdlm(fname_true)


    fname_true = "pf-true/zdt2-5.txt"
    pf5 = readdlm(fname_true)
    display(pf5)


    unary_res = []
    for nrun = 2:22
        res = get_unary_metric_values(nrun, pf5, pf10)
        push!(unary_res, res')
    end

    unary_res = vcat(unary_res...)
    test_and_tables(unary_res)
    
end

main()

