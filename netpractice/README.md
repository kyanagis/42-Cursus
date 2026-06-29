*This project has been created as part of the 42 curriculum by kyanagis.*

# NetPractice

## Description

NetPractice is a hands-on introduction to TCP/IP networking. Instead of writing
code, you work through a graphical training interface made of small network
topologies — hosts, switches, routers, and the wider Internet — and configure
them so that every machine can reach the others.

Each of the 10 levels presents a partially configured network with missing or
incorrect values: IP addresses, subnet masks, default gateways, and routing
table entries. The goal of every level is to fill in the blanks so that all the
required connections succeed. Completing the project means solving all 10 levels
and exporting each solved configuration.

The point of the exercise is conceptual rather than mechanical: you learn how IP
addressing and subnetting actually constrain which machines can talk to each
other, how a default gateway and a routing table decide where a packet goes
next, and why a misconfigured mask or route silently breaks connectivity.

## Instructions

This project has no source code to compile. The deliverable is the set of
exported level configurations produced with the official training interface.

> **Conventions.** The requirement keywords **MUST**, **SHOULD**, and **MAY**
> in this document are to be interpreted as described in
> [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119) and
> [RFC 8174](https://datatracker.ietf.org/doc/html/rfc8174).

### Running the training interface

1. Download the subject's training interface archive from the 42 intranet
   (NetPractice project page) and extract it.
2. Launch the interface:
   - Run the provided launcher: `./run.sh`
   - If the launcher cannot reach a browser, the page MUST be served over a
     local HTTP server (browsers refuse to load it from a `file://` origin):
     `python3 -m http.server 49242`, then open `http://localhost:49242`.
3. Enter your **intranet login** in the interface. The configuration is derived
   per login, so this step is mandatory for a valid submission.
4. Work through the levels in order, from **Level 1** to **Level 10**. Each level
   is validated independently by the interface itself: when a level is correct,
   the interface reports it as solved.

### Exporting a configuration

When a level is solved, use the interface's **Get my config** action to download
that level's configuration as a JSON file. Each file MUST be saved at the **root
of this repository**, named after its level:

```
level1.json
level2.json
...
level10.json
```

A configuration file is a compact JSON snapshot of the interfaces, IP addresses,
masks, gateways, and routes you set for that level. For example:

```json
{"routes":{},"ifs":{"A1":{"ip":"104.98.23.1"},"B1":{},"C1":{},"D1":{"ip":"211.191.0.42"}}}
```

### Submission requirements

- The repository root MUST contain **exactly 10 exported configuration files**,
  one per level: `level1.json` through `level10.json`.
- Each file MUST correspond to a **solved** state of its level.
- This `README.md` MUST be present and committed at the repository root.

To verify the configs are in place before submitting:

```sh
ls level{1,2,3,4,5,6,7,8,9,10}.json
```

During evaluation, the levels are reopened with these exported files to confirm
each configuration genuinely solves its topology.

## Resources

### Networking concepts, anchored to their defining standards

Working through the levels covers the core building blocks of IP networking.
Each is grounded in the document that standardizes it:

- **TCP/IP addressing** — the 32-bit IPv4 address and its network/host split are
  defined by the Internet Protocol, [RFC 791](https://datatracker.ietf.org/doc/html/rfc791).
  Host-side requirements, including how a host decides whether a destination is
  on-link, are specified in
  [RFC 1122](https://datatracker.ietf.org/doc/html/rfc1122).
- **Subnet masks and subnetting** — the subnet mask and the procedure for
  splitting an address into network and host portions come from
  [RFC 950](https://datatracker.ietf.org/doc/html/rfc950). Network and broadcast
  addresses, and the usable host range in between, follow directly from the mask.
- **CIDR notation (`/24`, `/27`, …)** — classless prefixes and aggregation are
  defined by [RFC 4632](https://datatracker.ietf.org/doc/html/rfc4632), which
  replaced the old class A/B/C scheme with variable-length prefixes.
- **Private address ranges** — the `10.0.0.0/8` and `192.168.0.0/16` blocks used
  in several levels are reserved for private internets by
  [RFC 1918](https://datatracker.ietf.org/doc/html/rfc1918).
- **Default gateway** — a host that needs to reach an address outside its own
  subnet forwards traffic to its configured gateway; this host behaviour is part
  of [RFC 1122](https://datatracker.ietf.org/doc/html/rfc1122).
- **Routers and switches** — a switch forwards within a single network at layer
  2, whereas a router forwards *between* networks at layer 3, with each interface
  belonging to a different subnet. Router requirements, including forwarding and
  routing-table behaviour, are specified in
  [RFC 1812](https://datatracker.ietf.org/doc/html/rfc1812).
- **Routing tables and the default route** — a router selects the next hop by
  longest-prefix match against its routing table; the default route `0.0.0.0/0`
  (least specific match, toward the Internet) and prefix matching are described
  in [RFC 1812](https://datatracker.ietf.org/doc/html/rfc1812) and
  [RFC 4632](https://datatracker.ietf.org/doc/html/rfc4632).
- **OSI layers** — situating addressing, switching, and routing in a layered
  model (notably layer 2 vs. layer 3) helps locate where a problem lives. The OSI
  reference model is standardized in **ISO/IEC 7498-1** (it is an ISO standard,
  not an RFC); the Internet's own layering is described in
  [RFC 1122](https://datatracker.ietf.org/doc/html/rfc1122).

### Reference material

- [RFC 1180 — A TCP/IP Tutorial](https://datatracker.ietf.org/doc/html/rfc1180)
  — a readable, end-to-end walkthrough of addressing, subnetting, and routing.
- [RFC 791 — Internet Protocol](https://datatracker.ietf.org/doc/html/rfc791),
  [RFC 950 — Internet Standard Subnetting Procedure](https://datatracker.ietf.org/doc/html/rfc950),
  and [RFC 4632 — CIDR](https://datatracker.ietf.org/doc/html/rfc4632) for the
  addressing and subnetting model.
- [RFC 1122 — Requirements for Internet Hosts](https://datatracker.ietf.org/doc/html/rfc1122)
  and [RFC 1812 — Requirements for IP Version 4 Routers](https://datatracker.ietf.org/doc/html/rfc1812)
  for host vs. router forwarding behaviour and default-gateway/routing rules.
- ISO/IEC 7498-1 — the OSI Basic Reference Model — for the layer model itself.
- A subnet/CIDR calculator for cross-checking masks, network addresses, and
  usable host ranges while solving levels. Note that the subject forbids external
  tools during the defense; only a basic calculator such as `bc` is tolerated, so
  it is worth learning to compute mask boundaries by hand.

### Use of AI

AI was used as a learning aid, not as a solver. Specifically:

- To explain and reinforce the underlying concepts — subnet mask boundaries,
  how a default gateway and routing table cooperate, and the layer 2 vs. layer 3
  distinction — when a level exposed a gap in my understanding.
- To sanity-check my reasoning on individual levels (for example, confirming
  whether two interfaces actually share a subnet under a given mask) after I had
  worked out the answer myself.
- To help draft and structure this `README.md` and to anchor its references to
  the relevant RFCs.

The exported configurations were solved and validated through the official
training interface.
