import DelimitedFiles: readdlm
import Metaheuristics: PerformanceIndicators
import LinearAlgebra: norm
import Statistics: mean, median, std
import HypothesisTests: MannWhitneyUTest, pvalue

# x is dominated by y
function is_dominated(y, x)
    flag = false
    for i = 1:length(x)
        if x[i] > y[i]
            return false
        end
        if x[i] < y[i]
            flag = true
        end
    end

    return flag
    
end


function spacing(A)
    n, m = size(A)

    d = zeros(n)
    for i = 1:n
        d[i] = minimum( [ sum( abs.(A[i,:] - A[j,:]) ) for j in deleteat!(collect(1:n), i) ] )
    end

    d_hat = mean(d)
    s = (1.0 / ( n - 1 )) * sum( (d_hat .- d) .^ 2 )
    return sqrt(s)
    
end

# A Matrix(n, m) : el frente optimo de pref
# 1 significa que todos los vectores de B son
# dominados por A. Lo opuesto, C(A, B) = 0
function covering(A, B)
    n_a, m = size(A)
    n_b, m = size(B)
    s = 0
    for i = 1:n_b
        for j = 1:n_a
            if is_dominated(A[j,:], B[i,:] )
                s += 1
                break
            end    
        end
        
    end

    return s / n_b
    
end


function get_front(fname)
    M_ = readdlm(fname, ' ')
    if size(M_, 2) == 6
        M_ = M_[:,1:5]

    elseif size(M_, 2) == 4
        M_ = M_[:,1:3]
    elseif size(M_, 2) == 11
        M_ = M_[:,1:10]
    end
    
    return M_
end


IGD(A, true_pareto_front) = PerformanceIndicators.igd(A, true_pareto_front)


function get_unary_metric_values(nrun)

    fname_tipo4 = "pf-approx/zcat3-3-run$(nrun).txt"
    fname_tipo5 = "pf-approx/zcat20-3-run$(nrun).txt"
    tipo4 = get_front(fname_tipo4)
    tipo5 = get_front(fname_tipo5)

    return [0, 0, 0, 0, spacing(tipo4), spacing(tipo5) ]

end

function test_and_tables(results, text)
    y_igd = results[:, 1]
    x_igd = [results[:, 2], results[:, 3]]
    y_sp = results[:, 4]
    x_sp = [results[:, 5], results[:, 6]]

    mmin = minimum(results, dims=1)
    mmax = maximum(results, dims=1)
    mmedian = median(results, dims=1)
    mmean = mean(results, dims=1)
    sstd = std(results, dims=1)

    stats = [ mmin' mmean' sstd' mmax' ]

    println(" & Min. & Mean & Std. & Max. \\\\ \\hline")
    for i = 1:size(stats,1)
        # print(text[i], " & ")
        print(join(string.( round.(stats[i,:], digits=4) ), " & "))
        println("\\\\")
    end

    print("\n============\n")
    print("\n p-values \n")
    print("\n============\n")

    print("IGD DTLZ2 vs  & ")
    
    
    for i in 1:length(x_sp)
        test_sp = MannWhitneyUTest(y_sp, x_sp[i])
        test_igd = MannWhitneyUTest(y_igd, x_igd[i])
        p_sp =  pvalue(test_sp)
        p_igd =  pvalue(test_igd)


        #println("IGD DTLZ2 & SP \$L_$(3+i)\$ \\\\ ")
        @show p_igd
        @show p_sp
        
        # signifficative difference?
        if p_igd < 0.05
            if median(x_igd[i]) < median(y_igd)
                print("\$ + \$")
            elseif median(x_igd[i]) > median(y_igd)
                print("\$ - \$")
            else
                print("\$ \\approx \$")
            end
        else
            print("\$ \\approx \$")
        end
        print(" & ")
        
        

        # signifficative difference?
        if p_sp < 0.05
            if median(x_sp[i]) < median(y_sp)
                print("\$ + \$")
            elseif median(x_sp[i]) > median(y_sp)
                print("\$ - \$")
            else
                print("\$ \\approx \$")
            end
        else
            print("\$ \\approx \$")
        end

        println("\\\\")
        
        
        
    end
    
    
    

end


function tables_coverage()

    A = zeros(3,2)
    for nrun in 2:31
        for nrun2 in 2:31
            fname_nsga = "pf-approx/zcat3-3-run$(nrun).txt"
            fname_moead = "pf-approx/zcat20-3-run$(nrun).txt"
            tipo4 = get_front(fname_nsga)
            tipo5 = get_front(fname_moead)

            # original vs L4, original vs L5, L4 vs L5
            # A[1,1] += covering([], tipo4)
            # A[1,2] += covering(tipo4, [])


            # A[2,1] += covering([], tipo5)
            # A[2,2] += covering(tipo5, original)


            A[3,1] += covering(tipo4, tipo5)
            A[3,2] += covering(tipo5, tipo4)
        end
    end

    A /= 31.0 
    A = round.(100A, digits=2)

    
    print("Covering")
    for i in 1:size(A,1)
        println( join(string.(A[i,:]), " & "), "\\\\" )
    end

end


function main()
    unary_res = []
    for nrun = 2:31
        res = get_unary_metric_values(nrun)
        push!(unary_res, res')
    end

    unary_res = vcat(unary_res...)
    test_and_tables(unary_res, "")
end

tables_coverage()

main()
