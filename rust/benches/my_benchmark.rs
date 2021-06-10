use rust::*;
use rand::prelude::*;
use criterion::{black_box, criterion_group, criterion_main, Criterion};

fn beautify_bench(c: &mut Criterion) {
    c.bench_function("beautify 10000", |b| {
        let lc = legal_codes();
        let codes: Vec<u16> = (0..10_000).map(|_| {
            lc[random::<usize>() % lc.len()]
        }).collect();

        b.iter(|| {
            for &code in codes.iter() {
                let _ = beautify(code);
            }
        });
    });
}

fn beautify_benchmanual(c: &mut Criterion) {
    c.bench_function("beautify_manual 10000", |b| {
        let lc = legal_codes();
        let codes: Vec<u16> = (0..10_000).map(|_| {
            lc[random::<usize>() % lc.len()]
        }).collect();

        b.iter(|| {
            for &code in codes.iter() {
                let _ = beautify_manual(code);
            }
        });
    });
}

fn beautify_benchcopy(c: &mut Criterion) {
    c.bench_function("beautify_copy 10000", |b| {
        let lc = legal_codes();
        let codes: Vec<u16> = (0..10_000).map(|_| {
            lc[random::<usize>() % lc.len()]
        }).collect();

        b.iter(|| {
            for &code in codes.iter() {
                let _ = beautify_copy(code);
            }
        });
    });
}

criterion_group!(benches, beautify_bench, beautify_benchcopy, beautify_benchmanual);
criterion_main!(benches);
