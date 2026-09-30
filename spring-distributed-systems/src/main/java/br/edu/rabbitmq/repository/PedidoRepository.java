package br.edu.rabbitmq.repository;

import br.edu.rabbitmq.model.Pedido;
import org.springframework.stereotype.Repository;

import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

/** Armazenamento em memória — o foco do projeto é a mensageria, não a persistência. */
@Repository
public class PedidoRepository {

    private final Map<Long, Pedido> pedidos = new ConcurrentHashMap<>();
    private final AtomicLong sequencia = new AtomicLong(1000);

    public Long proximoId() {
        return sequencia.incrementAndGet();
    }

    public Pedido salvar(Pedido pedido) {
        pedidos.put(pedido.id(), pedido);
        return pedido;
    }

    public Optional<Pedido> buscarPorId(Long id) {
        return Optional.ofNullable(pedidos.get(id));
    }

    public List<Pedido> listar() {
        return pedidos.values().stream()
                .sorted(Comparator.comparing(Pedido::id))
                .toList();
    }
}
