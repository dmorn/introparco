#!/usr/bin/env Rscript

library(tidyverse)

plot.mem <- function(df, a = "sumprefix") {
  df %>%
    group_by(free, alloc, memtot) %>%
    filter(algo == a) %>%
    ggplot() +
    ggtitle(a, subtitle = "memory measurements") +
    geom_line(aes(x = n, y = free, colour = "free()")) +
    geom_line(aes(x = n, y = alloc, colour = "alloc()")) +
    geom_line(aes(x = n, y = memtot, colour = "tot")) +
    scale_x_continuous("array size", labels = scales::label_number_si()) +
    scale_y_continuous("execution time (ms)") +
    facet_wrap(vars(ctx)) +
    theme(legend.position = "bottom", legend.title = element_blank())
}

plot.exec <- function(df, a = "sumprefix") {
  df %>%
    filter(algo == a) %>%
    ggplot() +
    ggtitle(a) +
    geom_line(aes(x = n, y = exec, colour = ctx)) +
    scale_x_continuous("array size", labels = scales::label_number_si()) +
    scale_y_continuous("execution time (ms)") +
    theme(legend.position = "bottom", legend.title = element_blank())
}

# main
names <- c("ctx", "algo", "n", "alloc", "free", "exec")

df <-
  file("stdin") %>%
  read_csv(col_names = names, col_types = cols()) %>%
  group_by(n, ctx, algo) %>%
  summarise(
    exec = mean(exec)/1e3,
    free = mean(free)/1e3,
    alloc = mean(alloc)/1e3,
  ) %>%
  mutate(
    memtot = alloc + free
  )

pdf("plot.pdf")

name <- "randsum"
plot.mem(df, a=name)
plot.exec(df, a=name)

name <- "sumprefix"
plot.mem(df, a=name)
plot.exec(df, a=name)

dev.off()
